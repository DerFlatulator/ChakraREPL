// ChakraREPL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ChakraCore.h"

#include <string>
#include <iostream>
#include <sstream>

class JsRuntime
{
public:
	JsRuntime()
	{
		// Create a runtime. 
		JsCreateRuntime(JsRuntimeAttributeNone, nullptr, &runtime_);
		// Create an execution context. 
		JsCreateContext(runtime_, &context_);
		// Now set the current execution context.
		JsSetCurrentContext(context_);
	}
	~JsRuntime()
	{
		// Dispose runtime
		JsSetCurrentContext(JS_INVALID_REFERENCE);
		JsDisposeRuntime(runtime_);
	}

	JsValueRef invokeScript(const std::wstring script)
	{
		JsValueRef result;
		// Run the script.
		const auto status = JsRunScript(script.c_str(), sourceContext_++, L"", &result);
		
		return valueOrError(result, status);
	}

	JsValueRef coerceToString(const JsValueRef value) const 
	{
		// Convert your script result to String in JavaScript; redundant if your script returns a String
		JsValueRef result;
		const auto status = JsConvertValueToString(value, &result);

		return valueOrError(result, status);
	}

	std::wstring extractString(const JsValueRef value) const 
	{
		// Project script result back to C++.
		const wchar_t* resultWC;
		size_t stringLength;
		JsStringToPointer(value, &resultWC, &stringLength);

		return std::wstring{ resultWC };
	}

	JsValueRef valueOrError(const JsValueRef& value, const JsErrorCode& status) const
	{
		if (status != JsNoError)
		{
			JsValueRef exception;
			// TODO: Actually handle this exception properly (print stack trace)
			JsGetAndClearException(&exception);

			if (status == JsErrorCode::JsErrorScriptCompile)
			{
				throw std::wstring{ L"Error: Script Compilation Error" };
			}
			if (status == JsErrorCode::JsErrorScriptException)
			{
				throw std::wstring{ L"Error: Script Execution Error" };
			}

			std::wstringstream wss;
			wss << L"Error: Unknown Error Occured [" << status << "]";
			throw wss.str();
		}

		return value;
	}

private:
	JsRuntimeHandle runtime_;
	JsContextRef context_;
	JsSourceContext sourceContext_;
};

class JsRepl
{
public:
	JsRepl(const std::string prompt)
		: prompt_(prompt)
	{}

	std::wstring read()
	{
		std::cout << prompt_;
		std::wstring script;	
		std::getline(std::wcin, script);
		return script;
	}

	std::wstring eval(std::wstring script)
	{
		try 
		{
			const JsValueRef value = jsRuntime_.invokeScript(script);
			const JsValueRef strValue = jsRuntime_.coerceToString(value);
			return jsRuntime_.extractString(strValue);
		}
		catch (const std::wstring& errorMessage)
		{
			return errorMessage;
		}

	}

	void print(std::wstring result)
	{
		std::wcout << result << std::endl;
	}

private:
	JsRuntime jsRuntime_;
	std::string prompt_;
};

int main()
{
	JsRepl jsRepl{ "chakra> " };

	while (true)
	{
		const std::wstring script = jsRepl.read();

		const std::wstring value = jsRepl.eval(script);

		jsRepl.print(value);
	}
	return 0;
}