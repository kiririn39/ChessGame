//
// Created by Vlad Boroday on 2023-04-15.
//

#include "Backward.h"
#include "backward.hpp"

std::ostringstream Backward::GetStackTrace()
{
	backward::TraceResolver resolver;
	static backward::SignalHandling sh;

	backward::StackTrace stackTrace;
	stackTrace.load_here(32);

	backward::Printer printer;
	printer.object = true;
	printer.color_mode = backward::ColorMode::always;
	printer.address = true;

	std::ostringstream stream;
	printer.print(stackTrace, stream);

	return stream;
}