#include "pch.hpp"

//CREDITS TO b1scoito for MOST of this injector

auto on_exit() -> void;

int WINAPI WinMain( _In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd )
{
	std::atexit( on_exit );

	// ~ get arguments
	//
	int argc; auto* argv = CommandLineToArgvW( GetCommandLineW(), &argc );

	// ~ if an argument is passed inject the target dll, so we can drag and drop the dll to the exe.
	//
	if ( argv[1] ) utils::vars::FTP_filename = utils::string::wstring_to_string( argv[1] );

	std::string proc_name;
	std::string methhead;
	std::string returnLib;
	std::cout << " _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ __    _____ _____ _____ _____ _____ " << std::endl;
	std::cout << "|   __|  |  |     |  |  |_   _|  |  |   __|  _  |     |  _  |  |  |  |  |  _  |_   _|     |     |   | |" << std::endl;
	std::cout << "|   __|  |  |   --|    -| | | |     |   __|   __|  |  |   __|  |  |  |__|     | | | |-   -|  |  | | | |" << std::endl;
	std::cout << "|__|  |_____|_____|__|__| |_| |__|__|_____|__|  |_____|__|  |_____|_____|__|__| |_| |_____|_____|_|___|" << std::endl;
	std::cout << "~ developed by n0verify and b1scoito. Thank you DarthTon for making BlackBone memory hacking library." << std::endl;
	log_debug("Injection Method:");
	log_debug("1 ) LoadLibrary");
	log_debug("2 ) ManualMap");
	std::cin >> methhead;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
	log_debug("Type csgo to start injection :");
	std::cin >> proc_name;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

	if (methhead == "1"| methhead == "loadlibrary" | methhead == "LoadLibrary" | methhead == "ll")
	{
		if (!g_injector.callLoadLib(proc_name))
		{
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}
	else if (methhead == "2" | methhead == "manualmap" | methhead == "ManualMap" | methhead == "mm")
	{
		if (!g_injector.call(proc_name))
		{
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}
	else
	{
		system("pause");
		ExitProcess(0);
	}
}

auto on_exit() -> void
{
	std::this_thread::sleep_for( 10s );
}