#pragma once

// Debug defines
#ifdef _DEBUG
#	define ifDebug(code) code
#else
#	define ifDebug(code)
#endif // _DEBUG