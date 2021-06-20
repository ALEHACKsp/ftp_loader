#include "pch.hpp"
#include "injection.hpp"

bool injector::map( std::string process, std::wstring module_name, std::vector<std::uint8_t> binary_bytes )
{
	// ~ wait for process to be opened
	//
	log_debug( "waiting for [ %s ] to be opened...", process.c_str() );

	auto process_list = memory::get_process_list();
	while ( true )
	{
		process_list = memory::get_process_list();
		if ( memory::is_process_open( process_list, process ) )
			break;

		std::this_thread::sleep_for( 500ms );
	}

	// ~ bypassing injection block by csgo (-allow_third_party_software) the easiest way
	//
	if ( process.find( "csgo" ) != std::string::npos )
	{
		const auto bypass_nt_open_file = []( DWORD pid )
		{
			const auto h_process = OpenProcess( PROCESS_ALL_ACCESS, false, pid );
			LPVOID nt_open_file = GetProcAddress( LoadLibrary( "ntdll" ), "NtOpenFile" );

			char original_bytes[5];

			// ~ copy 5 bytes to NtOpenFile procedure address
			//
			std::memcpy( original_bytes, nt_open_file, 5 );

			// ~ write it to memory
			//
			WriteProcessMemory( h_process, nt_open_file, original_bytes, 5, nullptr );

			CloseHandle( h_process );
		};

		bypass_nt_open_file( memory::get_process_id_by_name( process_list, process ) );
	}

	blackbone::Process bb_process;

	bb_process.Attach( memory::get_process_id_by_name( process_list, process ), PROCESS_ALL_ACCESS );

	log_debug( "injecting VAC3 bypass into [ %s ] waiting for [ %ls ]...", process.c_str(), module_name.c_str() );

	// ~ wait for a process module so we can continue with injection
	//
	auto mod_ready = false;
	while ( !mod_ready )
	{
		for ( const auto& mod : bb_process.modules().GetAllModules() )
		{
			if ( mod.first.first == module_name )
			{
				mod_ready = true;
				break;
			}
		}

		if ( mod_ready )
			break;

		std::this_thread::sleep_for( 500ms );
	}

	// ~ resolve PE imports
	//
	const auto mod_callback = []( blackbone::CallbackType type, void*, blackbone::Process&, const blackbone::ModuleData& modInfo )
	{
		std::string user32 = "user32.dll";
		if ( type == blackbone::PreCallback )
		{
			if ( modInfo.name == std::wstring( user32.begin(), user32.end() ) )
				return blackbone::LoadData( blackbone::MT_Native, blackbone::Ldr_Ignore );
		}
		return blackbone::LoadData( blackbone::MT_Default, blackbone::Ldr_Ignore );
	};

	// ~ mapping dll bytes to the process
	//
	if ( !bb_process.mmap().MapImage( binary_bytes.size(), binary_bytes.data(), false, blackbone::WipeHeader, mod_callback, nullptr, nullptr ).success() )
	{
		log_err( "failed to inject into [ %s ]!", process.c_str() );
		bb_process.Detach();

		return false;
	}

	// ~ free memory and detach from process
	//
	bb_process.Detach();

	log_ok( "VAC3 bypass module injected to [ %s ] successfully!", process.c_str() );
	return true;
}

bool injector::call( std::string process_name )
{
	if ( !std::filesystem::exists( utils::vars::FTP_filename ) )
	{
		log_err( "[ %s ] not found!", utils::vars::FTP_filename.c_str() );
		return false;
	}

	// ~ closing processes
	//
	close_processes( { process_name, "steam.exe" } );

	const auto steam_path = utils::other::get_steam_path();
	if ( steam_path.empty() )
	{
		log_err( "failed to retrieve steam path!" );
		return false;
	}

	log_debug( "opening steam [ %s ]...", steam_path.c_str() );

	PROCESS_INFORMATION pi{};
	if ( !memory::open_process( steam_path, { "-console" }, pi ) )
	{
		log_err( "failed to open steam!" );

		CloseHandle( pi.hProcess );
		CloseHandle( pi.hThread );

		return false;
	}

	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );

	std::vector<std::uint8_t> FTP{};

	// ~ reading file and writing it to a variable
	//
	if ( !utils::other::read_file_to_memory( std::filesystem::absolute( utils::vars::FTP_filename ).string(), &FTP ) )
	{
		log_err( "failed to write dll to memory!" );
		return false;
	}

	// ~ inject vac bypass to steam
	//
	if ( !map( "steam.exe", L"tier0_s.dll", vac3_data ) )
	{
		log_err( "steam memory mapping failure!" );
		return false;
	}

	// ~ inject FTP to process
	//
	if ( !map( process_name, L"serverbrowser.dll", FTP ) )
	{
		log_err( "FTP memory mapping failure!" );
		return false;
	}

	log_ok( "all done!" );
	return true;
}

void injector::close_processes( std::vector<std::string> processes )
{
	auto process_list = memory::get_process_list();
	for ( const auto& process : processes )
	{
		while ( true )
		{
			memory::kill_process( process_list, process );

			process_list = memory::get_process_list();
			if ( !memory::is_process_open( process_list, process ) )
				break;

			std::this_thread::sleep_for( 500ms );
		}
	}
}

void myPause() {
	log_err("Open CSGO FIRST, and then press any key to continue");
	getchar();
}
//DWORD pID = GetProcessId("csgo.exe");

bool LoadLibraryInject(DWORD ProcessId, const char* Dll)
{
	if (ProcessId == NULL)
		return false;

	char CustomDLL[MAX_PATH];
	GetFullPathName(Dll, MAX_PATH, CustomDLL, 0);

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);
	LPVOID allocatedMem = VirtualAllocEx(hProcess, NULL, sizeof(CustomDLL), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	if (!WriteProcessMemory(hProcess, allocatedMem, CustomDLL, sizeof(CustomDLL), NULL))
		return FALSE;

	CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, allocatedMem, 0, 0);

	if (hProcess)
		CloseHandle(hProcess);

	return TRUE;
}

bool injector::callLoadLib(std::string process_name)
{

	// ~ closing processes
	//
	close_processes({ process_name, "steam.exe" });

	const auto steam_path = utils::other::get_steam_path();
	if (steam_path.empty())
	{
		log_err("failed to retrieve steam path!");
		return false;
	}

	log_debug("opening steam [ %s ]...", steam_path.c_str());

	PROCESS_INFORMATION pi{};
	if (!memory::open_process(steam_path, { "-console" }, pi))
	{
		log_err("failed to open steam!");

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		return false;
	}

	//CloseHandle(pi.hProcess);
	//CloseHandle(pi.hThread);

	// ~ inject vac bypass to steam
	//
	if (!map("steam.exe", L"tier0_s.dll", vac3_data))
	{
		log_err("steam memory mapping failure!");
		return false;
	}


	log_debug("waiting for [ %s ] to be opened...", process_name.c_str());

	auto process_list = memory::get_process_list();
	while (true)
	{
		process_list = memory::get_process_list();
		if (memory::is_process_open(process_list, process_name))
			break;

		std::this_thread::sleep_for(500ms);
	}
	log_debug("starting... ");
	std::this_thread::sleep_for(15000ms);

	if (!std::filesystem::exists(utils::vars::FTP_filename))
	{
		log_err("[ %s ] not found!", utils::vars::FTP_filename.c_str());
		return false;
	}
	else
	{
		// ~ bypassing injection block by csgo (-allow_third_party_software) the easiest way
		if (process_name.find("csgo") != std::string::npos)
		{
			log_debug("starting byte vac bypass for [ %s ]", process_name.c_str());
			const auto bypass_nt_open_file = [](DWORD pid)
			{
				const auto h_process = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
				LPVOID nt_open_file = GetProcAddress(LoadLibrary("ntdll"), "NtOpenFile");

				char original_bytes[5];

				// ~ copy 5 bytes to NtOpenFile procedure address
				//

				std::memcpy(original_bytes, nt_open_file, 5);

				// ~ write it to memory
				//
				WriteProcessMemory(h_process, nt_open_file, original_bytes, 5, nullptr);

				CloseHandle(h_process);
			};
			log_debug("copying original bytes from [ %s ]", process_name.c_str());
			std::this_thread::sleep_for(1000ms);
			log_debug("replacing vac bytes with original in [ %s ]", process_name.c_str());
			bypass_nt_open_file(memory::get_process_id_by_name(process_list, process_name));
			std::this_thread::sleep_for(1000ms);
			log_ok("success!");
			std::this_thread::sleep_for(2000ms);
		}

		log_debug("injecting FTP into [ %s ]", process_name.c_str());
		std::this_thread::sleep_for(3000ms);
		LoadLibraryInject(memory::get_process_id_by_name(process_list, process_name), "FTP.dll");
		log_ok("success!");
	}

	log_ok("all done! window will automatically close.");
	return true;
}