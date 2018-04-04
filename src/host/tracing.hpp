/*++
Copyright (c) Microsoft Corporation

Module Name:
- tracing.hpp

Abstract:
- This module is used for recording tracing/debugging information to the telemetry ETW channel
- The data is not automatically broadcast to telemetry backends as it does not set the TELEMETRY keyword.
- NOTE: Many functions in this file appear to be copy/pastes. This is because the TraceLog documentation warns
        to not be "cute" in trying to reduce its macro usages with variables as it can cause unexpected behavior.

Author(s):
- Michael Niksa (miniksa)     25-Nov-2014
--*/

#pragma once

namespace Microsoft::Console::Interactivity::Win32
{
    class UiaTextRange;

    namespace UiaTextRangeTracing
    {
        enum class ApiCall;
        struct IApiMsg;
    }

    class ScreenInfoUiaProvider;

    namespace ScreenInfoUiaProviderTracing
    {
        enum class ApiCall;
        struct IApiMsg;
    }

    class WindowUiaProvider;

    namespace WindowUiaProviderTracing
    {
        enum class ApiCall;
        struct IApiMsg;
    }
}

#if DBG
#define DBGCHARS(_params_)   { Tracing::s_TraceChars _params_ ; }
#define DBGOUTPUT(_params_)  { Tracing::s_TraceOutput _params_ ; }
#else
#define DBGCHARS(_params_)
#define DBGOUTPUT(_params_)
#endif

class Tracing
{
public:
    static void s_TraceApi(const NTSTATUS status, const CONSOLE_GETLARGESTWINDOWSIZE_MSG* const a);
    static void s_TraceApi(const NTSTATUS status, const CONSOLE_SCREENBUFFERINFO_MSG* const a, _In_ bool const fSet);
    static void s_TraceApi(const NTSTATUS status, const CONSOLE_SETSCREENBUFFERSIZE_MSG* const a);
    static void s_TraceApi(const NTSTATUS status, const CONSOLE_SETWINDOWINFO_MSG* const a);

    static void s_TraceApi(_In_ void* buffer, const CONSOLE_WRITECONSOLE_MSG* const a);

    static void s_TraceApi(const CONSOLE_SCREENBUFFERINFO_MSG* const a);
    static void s_TraceApi(const CONSOLE_MODE_MSG* const a, const std::wstring& handleType);
    static void s_TraceApi(const CONSOLE_SETTEXTATTRIBUTE_MSG* const a);
    static void s_TraceApi(const CONSOLE_WRITECONSOLEOUTPUTSTRING_MSG* const a);

    static void s_TraceWindowViewport(const SMALL_RECT viewport);

    static void s_TraceChars(_In_z_ const char* pszMessage, ...);
    static void s_TraceOutput(_In_z_ const char* pszMessage, ...);

    static void s_TraceWindowMessage(const MSG& msg);
    static void s_TraceInputRecord(const INPUT_RECORD& inputRecord);

    static void __stdcall TraceFailure(const wil::FailureInfo& failure) noexcept;

    static void s_TraceUia(const Microsoft::Console::Interactivity::Win32::UiaTextRange* const range,
                           const Microsoft::Console::Interactivity::Win32::UiaTextRangeTracing::ApiCall apiCall,
                           const Microsoft::Console::Interactivity::Win32::UiaTextRangeTracing::IApiMsg* const apiMsg);

    static void s_TraceUia(const Microsoft::Console::Interactivity::Win32::ScreenInfoUiaProvider* const pProvider,
                           const Microsoft::Console::Interactivity::Win32::ScreenInfoUiaProviderTracing::ApiCall apiCall,
                           const Microsoft::Console::Interactivity::Win32::ScreenInfoUiaProviderTracing::IApiMsg* const apiMsg);

    static void s_TraceUia(const Microsoft::Console::Interactivity::Win32::WindowUiaProvider* const pProvider,
                           const Microsoft::Console::Interactivity::Win32::WindowUiaProviderTracing::ApiCall apiCall,
                           const Microsoft::Console::Interactivity::Win32::WindowUiaProviderTracing::IApiMsg* const apiMsg);

private:
    static ULONG s_ulDebugFlag;

    static const wchar_t* const _textPatternRangeEndpointToString(int endpoint);
    static const wchar_t* const _textUnitToString(int unit);
    static const wchar_t* const _eventIdToString(long eventId);
    static const wchar_t* const _directionToString(int direction);
};
