/*++

Copyright (C) 2019 PrimeDevelopers

All rights reserved.

This file has been generated by the Automatic Component Toolkit (ACT) version 1.5.0.

Abstract: This is an autogenerated C++-Header file in order to allow an easy
 use of Prime Numbers Library

Interface version: 1.2.0

*/

#ifndef __LIBPRIMES_CPPHEADER_DYNAMIC_CPP
#define __LIBPRIMES_CPPHEADER_DYNAMIC_CPP

#include "libprimes_types.hpp"
#include "libprimes_dynamic.h"

#ifdef _WIN32
#include <Windows.h>
#else // _WIN32
#include <dlfcn.h>
#endif // _WIN32
#include <string>
#include <memory>
#include <vector>
#include <exception>

namespace LibPrimes {

/*************************************************************************************************************************
 Forward Declaration of all classes
**************************************************************************************************************************/
class CWrapper;
class CBase;
class CCalculator;
class CFactorizationCalculator;
class CSieveCalculator;

/*************************************************************************************************************************
 Declaration of deprecated class types
**************************************************************************************************************************/
typedef CWrapper CLibPrimesWrapper;
typedef CBase CLibPrimesBase;
typedef CCalculator CLibPrimesCalculator;
typedef CFactorizationCalculator CLibPrimesFactorizationCalculator;
typedef CSieveCalculator CLibPrimesSieveCalculator;

/*************************************************************************************************************************
 Declaration of shared pointer types
**************************************************************************************************************************/
typedef std::shared_ptr<CWrapper> PWrapper;
typedef std::shared_ptr<CBase> PBase;
typedef std::shared_ptr<CCalculator> PCalculator;
typedef std::shared_ptr<CFactorizationCalculator> PFactorizationCalculator;
typedef std::shared_ptr<CSieveCalculator> PSieveCalculator;

/*************************************************************************************************************************
 Declaration of deprecated shared pointer types
**************************************************************************************************************************/
typedef PWrapper PLibPrimesWrapper;
typedef PBase PLibPrimesBase;
typedef PCalculator PLibPrimesCalculator;
typedef PFactorizationCalculator PLibPrimesFactorizationCalculator;
typedef PSieveCalculator PLibPrimesSieveCalculator;


/*************************************************************************************************************************
 Class ELibPrimesException 
**************************************************************************************************************************/
class ELibPrimesException : public std::exception {
protected:
	/**
	* Error code for the Exception.
	*/
	LibPrimesResult m_errorCode;
	/**
	* Error message for the Exception.
	*/
	std::string m_errorMessage;

public:
	/**
	* Exception Constructor.
	*/
	ELibPrimesException(LibPrimesResult errorCode, const std::string & sErrorMessage)
		: m_errorMessage("LibPrimes Error " + std::to_string(errorCode) + " (" + sErrorMessage + ")")
	{
		m_errorCode = errorCode;
	}

	/**
	* Returns error code
	*/
	LibPrimesResult getErrorCode() const noexcept
	{
		return m_errorCode;
	}

	/**
	* Returns error message
	*/
	const char* what() const noexcept
	{
		return m_errorMessage.c_str();
	}

};

/*************************************************************************************************************************
 Class CInputVector
**************************************************************************************************************************/
template <typename T>
class CInputVector {
private:
	
	const T* m_data;
	size_t m_size;
	
public:
	
	CInputVector( const std::vector<T>& vec)
		: m_data( vec.data() ), m_size( vec.size() )
	{
	}
	
	CInputVector( const T* in_data, size_t in_size)
		: m_data( in_data ), m_size(in_size )
	{
	}
	
	const T* data() const
	{
		return m_data;
	}
	
	size_t size() const
	{
		return m_size;
	}
	
};

// declare deprecated class name
template<typename T>
using CLibPrimesInputVector = CInputVector<T>;

/*************************************************************************************************************************
 Class CWrapper 
**************************************************************************************************************************/
class CWrapper {
public:
	
	CWrapper(const std::string &sFileName)
	{
		CheckError(nullptr, initWrapperTable(&m_WrapperTable));
		CheckError(nullptr, loadWrapperTable(&m_WrapperTable, sFileName.c_str()));
		
		CheckError(nullptr, checkBinaryVersion());
	}
	
	static PWrapper loadLibrary(const std::string &sFileName)
	{
		return std::make_shared<CWrapper>(sFileName);
	}
	
	~CWrapper()
	{
		releaseWrapperTable(&m_WrapperTable);
	}
	
	inline void CheckError(CBase * pBaseClass, LibPrimesResult nResult);

	inline bool GetLastError(CBase * pInstance, std::string & sErrorMessage);
	inline void ReleaseInstance(CBase * pInstance);
	inline void GetLibraryVersion(LibPrimes_uint32 & nMajor, LibPrimes_uint32 & nMinor, LibPrimes_uint32 & nMicro, std::string & sPreReleaseInfo, std::string & sBuildInfo);
	inline PFactorizationCalculator CreateFactorizationCalculator();
	inline PSieveCalculator CreateSieveCalculator();
	inline void SetJournal(const std::string & sFileName);

private:
	sLibPrimesDynamicWrapperTable m_WrapperTable;
	
	LibPrimesResult checkBinaryVersion()
	{
		LibPrimes_uint32 nMajor, nMinor, nMicro;
		std::string sPreReleaseInfo, sBuildInfo;
		GetLibraryVersion(nMajor, nMinor, nMicro, sPreReleaseInfo, sBuildInfo);
		if ( (nMajor != LIBPRIMES_VERSION_MAJOR) || (nMinor < LIBPRIMES_VERSION_MINOR) ) {
			return LIBPRIMES_ERROR_INCOMPATIBLEBINARYVERSION;
		}
		return LIBPRIMES_SUCCESS;
	}
	LibPrimesResult initWrapperTable(sLibPrimesDynamicWrapperTable * pWrapperTable);
	LibPrimesResult releaseWrapperTable(sLibPrimesDynamicWrapperTable * pWrapperTable);
	LibPrimesResult loadWrapperTable(sLibPrimesDynamicWrapperTable * pWrapperTable, const char * pLibraryFileName);

	friend class CBase;
	friend class CCalculator;
	friend class CFactorizationCalculator;
	friend class CSieveCalculator;

};

	
/*************************************************************************************************************************
 Class CBase 
**************************************************************************************************************************/
class CBase {
public:
	
protected:
	/* Wrapper Object that created the class. */
	CWrapper * m_pWrapper;
	/* Handle to Instance in library*/
	LibPrimesHandle m_pHandle;

	/* Checks for an Error code and raises Exceptions */
	void CheckError(LibPrimesResult nResult)
	{
		if (m_pWrapper != nullptr)
			m_pWrapper->CheckError(this, nResult);
	}

	/**
	* CBase::CBase - Constructor for Base class.
	*/
	CBase(CWrapper * pWrapper, LibPrimesHandle pHandle)
		: m_pWrapper(pWrapper), m_pHandle(pHandle)
	{
	}

	/**
	* CBase::~CBase - Destructor for Base class.
	*/
	virtual ~CBase()
	{
		if (m_pWrapper != nullptr)
			m_pWrapper->ReleaseInstance(this);
		m_pWrapper = nullptr;
	}

public:
	/**
	* CBase::GetHandle - Returns handle to instance.
	*/
	LibPrimesHandle GetHandle()
	{
		return m_pHandle;
	}
	
	friend class CWrapper;
};
	
/*************************************************************************************************************************
 Class CCalculator 
**************************************************************************************************************************/
class CCalculator : public CBase {
public:
	
	/**
	* CCalculator::CCalculator - Constructor for Calculator class.
	*/
	CCalculator(CWrapper* pWrapper, LibPrimesHandle pHandle)
		: CBase(pWrapper, pHandle)
	{
	}
	
	inline LibPrimes_uint64 GetValue();
	inline void SetValue(const LibPrimes_uint64 nValue);
	inline void Calculate();
	inline void SetProgressCallback(const ProgressCallback pProgressCallback);
};
	
/*************************************************************************************************************************
 Class CFactorizationCalculator 
**************************************************************************************************************************/
class CFactorizationCalculator : public CCalculator {
public:
	
	/**
	* CFactorizationCalculator::CFactorizationCalculator - Constructor for FactorizationCalculator class.
	*/
	CFactorizationCalculator(CWrapper* pWrapper, LibPrimesHandle pHandle)
		: CCalculator(pWrapper, pHandle)
	{
	}
	
	inline void GetPrimeFactors(std::vector<sPrimeFactor> & PrimeFactorsBuffer);
};
	
/*************************************************************************************************************************
 Class CSieveCalculator 
**************************************************************************************************************************/
class CSieveCalculator : public CCalculator {
public:
	
	/**
	* CSieveCalculator::CSieveCalculator - Constructor for SieveCalculator class.
	*/
	CSieveCalculator(CWrapper* pWrapper, LibPrimesHandle pHandle)
		: CCalculator(pWrapper, pHandle)
	{
	}
	
	inline void GetPrimes(std::vector<LibPrimes_uint64> & PrimesBuffer);
};
	
	/**
	* CWrapper::GetLastError - Returns the last error recorded on this object
	* @param[in] pInstance - Instance Handle
	* @param[out] sErrorMessage - Message of the last error
	* @return Is there a last error to query
	*/
	inline bool CWrapper::GetLastError(CBase * pInstance, std::string & sErrorMessage)
	{
		LibPrimesHandle hInstance = nullptr;
		if (pInstance != nullptr) {
			hInstance = pInstance->GetHandle();
		};
		LibPrimes_uint32 bytesNeededErrorMessage = 0;
		LibPrimes_uint32 bytesWrittenErrorMessage = 0;
		bool resultHasError = 0;
		CheckError(nullptr,m_WrapperTable.m_GetLastError(hInstance, 0, &bytesNeededErrorMessage, nullptr, &resultHasError));
		std::vector<char> bufferErrorMessage;
		bufferErrorMessage.resize(bytesNeededErrorMessage + 2);
		CheckError(nullptr,m_WrapperTable.m_GetLastError(hInstance, bytesNeededErrorMessage + 2, &bytesWrittenErrorMessage, &bufferErrorMessage[0], &resultHasError));
		bufferErrorMessage[bytesNeededErrorMessage + 1] = 0;
		sErrorMessage = std::string(&bufferErrorMessage[0]);
		return resultHasError;
	}
	
	/**
	* CWrapper::ReleaseInstance - Releases the memory of an Instance
	* @param[in] pInstance - Instance Handle
	*/
	inline void CWrapper::ReleaseInstance(CBase * pInstance)
	{
		LibPrimesHandle hInstance = nullptr;
		if (pInstance != nullptr) {
			hInstance = pInstance->GetHandle();
		};
		CheckError(nullptr,m_WrapperTable.m_ReleaseInstance(hInstance));
	}
	
	/**
	* CWrapper::GetLibraryVersion - retrieves the binary version of this library.
	* @param[out] nMajor - returns the major version of this library
	* @param[out] nMinor - returns the minor version of this library
	* @param[out] nMicro - returns the micro version of this library
	* @param[out] sPreReleaseInfo - returns pre-release info of this library (if this is a pre-release binary)
	* @param[out] sBuildInfo - returns build-information of this library (optional)
	*/
	inline void CWrapper::GetLibraryVersion(LibPrimes_uint32 & nMajor, LibPrimes_uint32 & nMinor, LibPrimes_uint32 & nMicro, std::string & sPreReleaseInfo, std::string & sBuildInfo)
	{
		LibPrimes_uint32 bytesNeededPreReleaseInfo = 0;
		LibPrimes_uint32 bytesWrittenPreReleaseInfo = 0;
		LibPrimes_uint32 bytesNeededBuildInfo = 0;
		LibPrimes_uint32 bytesWrittenBuildInfo = 0;
		CheckError(nullptr,m_WrapperTable.m_GetLibraryVersion(&nMajor, &nMinor, &nMicro, 0, &bytesNeededPreReleaseInfo, nullptr, 0, &bytesNeededBuildInfo, nullptr));
		std::vector<char> bufferPreReleaseInfo;
		bufferPreReleaseInfo.resize(bytesNeededPreReleaseInfo + 2);
		std::vector<char> bufferBuildInfo;
		bufferBuildInfo.resize(bytesNeededBuildInfo + 2);
		CheckError(nullptr,m_WrapperTable.m_GetLibraryVersion(&nMajor, &nMinor, &nMicro, bytesNeededPreReleaseInfo + 2, &bytesWrittenPreReleaseInfo, &bufferPreReleaseInfo[0], bytesNeededBuildInfo + 2, &bytesWrittenBuildInfo, &bufferBuildInfo[0]));
		bufferPreReleaseInfo[bytesNeededPreReleaseInfo + 1] = 0;
		sPreReleaseInfo = std::string(&bufferPreReleaseInfo[0]);
		bufferBuildInfo[bytesNeededBuildInfo + 1] = 0;
		sBuildInfo = std::string(&bufferBuildInfo[0]);
	}
	
	/**
	* CWrapper::CreateFactorizationCalculator - Creates a new FactorizationCalculator instance
	* @return New FactorizationCalculator instance
	*/
	inline PFactorizationCalculator CWrapper::CreateFactorizationCalculator()
	{
		LibPrimesHandle hInstance = nullptr;
		CheckError(nullptr,m_WrapperTable.m_CreateFactorizationCalculator(&hInstance));
		return std::make_shared<CFactorizationCalculator>(this, hInstance);
	}
	
	/**
	* CWrapper::CreateSieveCalculator - Creates a new SieveCalculator instance
	* @return New SieveCalculator instance
	*/
	inline PSieveCalculator CWrapper::CreateSieveCalculator()
	{
		LibPrimesHandle hInstance = nullptr;
		CheckError(nullptr,m_WrapperTable.m_CreateSieveCalculator(&hInstance));
		return std::make_shared<CSieveCalculator>(this, hInstance);
	}
	
	/**
	* CWrapper::SetJournal - Handles Library Journaling
	* @param[in] sFileName - Journal FileName
	*/
	inline void CWrapper::SetJournal(const std::string & sFileName)
	{
		CheckError(nullptr,m_WrapperTable.m_SetJournal(sFileName.c_str()));
	}
	
	inline void CWrapper::CheckError(CBase * pBaseClass, LibPrimesResult nResult)
	{
		if (nResult != 0) {
			std::string sErrorMessage;
			if (pBaseClass != nullptr) {
				GetLastError(pBaseClass, sErrorMessage);
			}
			throw ELibPrimesException(nResult, sErrorMessage);
		}
	}
	

	inline LibPrimesResult CWrapper::initWrapperTable(sLibPrimesDynamicWrapperTable * pWrapperTable)
	{
		if (pWrapperTable == nullptr)
			return LIBPRIMES_ERROR_INVALIDPARAM;
		
		pWrapperTable->m_LibraryHandle = nullptr;
		pWrapperTable->m_Calculator_GetValue = nullptr;
		pWrapperTable->m_Calculator_SetValue = nullptr;
		pWrapperTable->m_Calculator_Calculate = nullptr;
		pWrapperTable->m_Calculator_SetProgressCallback = nullptr;
		pWrapperTable->m_FactorizationCalculator_GetPrimeFactors = nullptr;
		pWrapperTable->m_SieveCalculator_GetPrimes = nullptr;
		pWrapperTable->m_GetLastError = nullptr;
		pWrapperTable->m_ReleaseInstance = nullptr;
		pWrapperTable->m_GetLibraryVersion = nullptr;
		pWrapperTable->m_CreateFactorizationCalculator = nullptr;
		pWrapperTable->m_CreateSieveCalculator = nullptr;
		pWrapperTable->m_SetJournal = nullptr;
		
		return LIBPRIMES_SUCCESS;
	}

	inline LibPrimesResult CWrapper::releaseWrapperTable(sLibPrimesDynamicWrapperTable * pWrapperTable)
	{
		if (pWrapperTable == nullptr)
			return LIBPRIMES_ERROR_INVALIDPARAM;
		
		if (pWrapperTable->m_LibraryHandle != nullptr) {
		#ifdef _WIN32
			HMODULE hModule = (HMODULE) pWrapperTable->m_LibraryHandle;
			FreeLibrary(hModule);
		#else // _WIN32
			dlclose(pWrapperTable->m_LibraryHandle);
		#endif // _WIN32
			return initWrapperTable(pWrapperTable);
		}
		
		return LIBPRIMES_SUCCESS;
	}

	inline LibPrimesResult CWrapper::loadWrapperTable(sLibPrimesDynamicWrapperTable * pWrapperTable, const char * pLibraryFileName)
	{
		if (pWrapperTable == nullptr)
			return LIBPRIMES_ERROR_INVALIDPARAM;
		if (pLibraryFileName == nullptr)
			return LIBPRIMES_ERROR_INVALIDPARAM;
		
		#ifdef _WIN32
		// Convert filename to UTF16-string
		int nLength = (int)strlen(pLibraryFileName);
		int nBufferSize = nLength * 2 + 2;
		std::vector<wchar_t> wsLibraryFileName(nBufferSize);
		int nResult = MultiByteToWideChar(CP_UTF8, 0, pLibraryFileName, nLength, &wsLibraryFileName[0], nBufferSize);
		if (nResult == 0)
			return LIBPRIMES_ERROR_COULDNOTLOADLIBRARY;
		
		HMODULE hLibrary = LoadLibraryW(wsLibraryFileName.data());
		if (hLibrary == 0) 
			return LIBPRIMES_ERROR_COULDNOTLOADLIBRARY;
		#else // _WIN32
		void* hLibrary = dlopen(pLibraryFileName, RTLD_LAZY);
		if (hLibrary == 0) 
			return LIBPRIMES_ERROR_COULDNOTLOADLIBRARY;
		dlerror();
		#endif // _WIN32
		
		#ifdef _WIN32
		pWrapperTable->m_Calculator_GetValue = (PLibPrimesCalculator_GetValuePtr) GetProcAddress(hLibrary, "libprimes_calculator_getvalue");
		#else // _WIN32
		pWrapperTable->m_Calculator_GetValue = (PLibPrimesCalculator_GetValuePtr) dlsym(hLibrary, "libprimes_calculator_getvalue");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_Calculator_GetValue == nullptr)
			return LIBPRIMES_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_Calculator_SetValue = (PLibPrimesCalculator_SetValuePtr) GetProcAddress(hLibrary, "libprimes_calculator_setvalue");
		#else // _WIN32
		pWrapperTable->m_Calculator_SetValue = (PLibPrimesCalculator_SetValuePtr) dlsym(hLibrary, "libprimes_calculator_setvalue");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_Calculator_SetValue == nullptr)
			return LIBPRIMES_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_Calculator_Calculate = (PLibPrimesCalculator_CalculatePtr) GetProcAddress(hLibrary, "libprimes_calculator_calculate");
		#else // _WIN32
		pWrapperTable->m_Calculator_Calculate = (PLibPrimesCalculator_CalculatePtr) dlsym(hLibrary, "libprimes_calculator_calculate");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_Calculator_Calculate == nullptr)
			return LIBPRIMES_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_Calculator_SetProgressCallback = (PLibPrimesCalculator_SetProgressCallbackPtr) GetProcAddress(hLibrary, "libprimes_calculator_setprogresscallback");
		#else // _WIN32
		pWrapperTable->m_Calculator_SetProgressCallback = (PLibPrimesCalculator_SetProgressCallbackPtr) dlsym(hLibrary, "libprimes_calculator_setprogresscallback");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_Calculator_SetProgressCallback == nullptr)
			return LIBPRIMES_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_FactorizationCalculator_GetPrimeFactors = (PLibPrimesFactorizationCalculator_GetPrimeFactorsPtr) GetProcAddress(hLibrary, "libprimes_factorizationcalculator_getprimefactors");
		#else // _WIN32
		pWrapperTable->m_FactorizationCalculator_GetPrimeFactors = (PLibPrimesFactorizationCalculator_GetPrimeFactorsPtr) dlsym(hLibrary, "libprimes_factorizationcalculator_getprimefactors");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_FactorizationCalculator_GetPrimeFactors == nullptr)
			return LIBPRIMES_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_SieveCalculator_GetPrimes = (PLibPrimesSieveCalculator_GetPrimesPtr) GetProcAddress(hLibrary, "libprimes_sievecalculator_getprimes");
		#else // _WIN32
		pWrapperTable->m_SieveCalculator_GetPrimes = (PLibPrimesSieveCalculator_GetPrimesPtr) dlsym(hLibrary, "libprimes_sievecalculator_getprimes");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_SieveCalculator_GetPrimes == nullptr)
			return LIBPRIMES_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_GetLastError = (PLibPrimesGetLastErrorPtr) GetProcAddress(hLibrary, "libprimes_getlasterror");
		#else // _WIN32
		pWrapperTable->m_GetLastError = (PLibPrimesGetLastErrorPtr) dlsym(hLibrary, "libprimes_getlasterror");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_GetLastError == nullptr)
			return LIBPRIMES_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_ReleaseInstance = (PLibPrimesReleaseInstancePtr) GetProcAddress(hLibrary, "libprimes_releaseinstance");
		#else // _WIN32
		pWrapperTable->m_ReleaseInstance = (PLibPrimesReleaseInstancePtr) dlsym(hLibrary, "libprimes_releaseinstance");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_ReleaseInstance == nullptr)
			return LIBPRIMES_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_GetLibraryVersion = (PLibPrimesGetLibraryVersionPtr) GetProcAddress(hLibrary, "libprimes_getlibraryversion");
		#else // _WIN32
		pWrapperTable->m_GetLibraryVersion = (PLibPrimesGetLibraryVersionPtr) dlsym(hLibrary, "libprimes_getlibraryversion");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_GetLibraryVersion == nullptr)
			return LIBPRIMES_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_CreateFactorizationCalculator = (PLibPrimesCreateFactorizationCalculatorPtr) GetProcAddress(hLibrary, "libprimes_createfactorizationcalculator");
		#else // _WIN32
		pWrapperTable->m_CreateFactorizationCalculator = (PLibPrimesCreateFactorizationCalculatorPtr) dlsym(hLibrary, "libprimes_createfactorizationcalculator");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_CreateFactorizationCalculator == nullptr)
			return LIBPRIMES_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_CreateSieveCalculator = (PLibPrimesCreateSieveCalculatorPtr) GetProcAddress(hLibrary, "libprimes_createsievecalculator");
		#else // _WIN32
		pWrapperTable->m_CreateSieveCalculator = (PLibPrimesCreateSieveCalculatorPtr) dlsym(hLibrary, "libprimes_createsievecalculator");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_CreateSieveCalculator == nullptr)
			return LIBPRIMES_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		#ifdef _WIN32
		pWrapperTable->m_SetJournal = (PLibPrimesSetJournalPtr) GetProcAddress(hLibrary, "libprimes_setjournal");
		#else // _WIN32
		pWrapperTable->m_SetJournal = (PLibPrimesSetJournalPtr) dlsym(hLibrary, "libprimes_setjournal");
		dlerror();
		#endif // _WIN32
		if (pWrapperTable->m_SetJournal == nullptr)
			return LIBPRIMES_ERROR_COULDNOTFINDLIBRARYEXPORT;
		
		pWrapperTable->m_LibraryHandle = hLibrary;
		return LIBPRIMES_SUCCESS;
	}
	
	
	/**
	 * Method definitions for class CBase
	 */
	
	/**
	 * Method definitions for class CCalculator
	 */
	
	LibPrimes_uint64 CCalculator::GetValue()
	{
		LibPrimes_uint64 resultValue = 0;
		CheckError(m_pWrapper->m_WrapperTable.m_Calculator_GetValue(m_pHandle, &resultValue));
		return resultValue;
	}
	
	void CCalculator::SetValue(const LibPrimes_uint64 nValue)
	{
		CheckError(m_pWrapper->m_WrapperTable.m_Calculator_SetValue(m_pHandle, nValue));
	}
	
	void CCalculator::Calculate()
	{
		CheckError(m_pWrapper->m_WrapperTable.m_Calculator_Calculate(m_pHandle));
	}
	
	void CCalculator::SetProgressCallback(const ProgressCallback pProgressCallback)
	{
		CheckError(m_pWrapper->m_WrapperTable.m_Calculator_SetProgressCallback(m_pHandle, pProgressCallback));
	}
	
	/**
	 * Method definitions for class CFactorizationCalculator
	 */
	
	void CFactorizationCalculator::GetPrimeFactors(std::vector<sPrimeFactor> & PrimeFactorsBuffer)
	{
		LibPrimes_uint64 elementsNeededPrimeFactors = 0;
		LibPrimes_uint64 elementsWrittenPrimeFactors = 0;
		CheckError(m_pWrapper->m_WrapperTable.m_FactorizationCalculator_GetPrimeFactors(m_pHandle, 0, &elementsNeededPrimeFactors, nullptr));
		PrimeFactorsBuffer.resize((size_t) elementsNeededPrimeFactors);
		CheckError(m_pWrapper->m_WrapperTable.m_FactorizationCalculator_GetPrimeFactors(m_pHandle, elementsNeededPrimeFactors, &elementsWrittenPrimeFactors, PrimeFactorsBuffer.data()));
	}
	
	/**
	 * Method definitions for class CSieveCalculator
	 */
	
	void CSieveCalculator::GetPrimes(std::vector<LibPrimes_uint64> & PrimesBuffer)
	{
		LibPrimes_uint64 elementsNeededPrimes = 0;
		LibPrimes_uint64 elementsWrittenPrimes = 0;
		CheckError(m_pWrapper->m_WrapperTable.m_SieveCalculator_GetPrimes(m_pHandle, 0, &elementsNeededPrimes, nullptr));
		PrimesBuffer.resize((size_t) elementsNeededPrimes);
		CheckError(m_pWrapper->m_WrapperTable.m_SieveCalculator_GetPrimes(m_pHandle, elementsNeededPrimes, &elementsWrittenPrimes, PrimesBuffer.data()));
	}

} // namespace LibPrimes

#endif // __LIBPRIMES_CPPHEADER_DYNAMIC_CPP

