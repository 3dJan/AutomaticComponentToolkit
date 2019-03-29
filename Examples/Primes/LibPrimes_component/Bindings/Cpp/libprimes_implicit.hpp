/*++

Copyright (C) 2019 PrimeDevelopers

All rights reserved.

This file has been generated by the Automatic Component Toolkit (ACT) version 1.5.0.

Abstract: This is an autogenerated C++-Header file in order to allow an easy
 use of Prime Numbers Library

Interface version: 1.2.0

*/

#ifndef __LIBPRIMES_CPPHEADER_IMPLICIT_CPP
#define __LIBPRIMES_CPPHEADER_IMPLICIT_CPP

#include "libprimes_types.hpp"
#include "libprimes_abi.hpp"

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
	
	CWrapper()
	{
	}
	
	~CWrapper()
	{
	}
	static inline PWrapper loadLibrary()
	{
		return std::make_shared<CWrapper>();
	}
	
	inline void CheckError(CBase * pBaseClass, LibPrimesResult nResult);

	inline bool GetLastError(CBase * pInstance, std::string & sErrorMessage);
	inline void ReleaseInstance(CBase * pInstance);
	inline void GetLibraryVersion(LibPrimes_uint32 & nMajor, LibPrimes_uint32 & nMinor, LibPrimes_uint32 & nMicro, std::string & sPreReleaseInfo, std::string & sBuildInfo);
	inline PFactorizationCalculator CreateFactorizationCalculator();
	inline PSieveCalculator CreateSieveCalculator();
	inline void SetJournal(const std::string & sFileName);

private:
	
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
		CheckError(nullptr,libprimes_getlasterror(hInstance, 0, &bytesNeededErrorMessage, nullptr, &resultHasError));
		std::vector<char> bufferErrorMessage;
		bufferErrorMessage.resize(bytesNeededErrorMessage + 2);
		CheckError(nullptr,libprimes_getlasterror(hInstance, bytesNeededErrorMessage + 2, &bytesWrittenErrorMessage, &bufferErrorMessage[0], &resultHasError));
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
		CheckError(nullptr,libprimes_releaseinstance(hInstance));
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
		CheckError(nullptr,libprimes_getlibraryversion(&nMajor, &nMinor, &nMicro, 0, &bytesNeededPreReleaseInfo, nullptr, 0, &bytesNeededBuildInfo, nullptr));
		std::vector<char> bufferPreReleaseInfo;
		bufferPreReleaseInfo.resize(bytesNeededPreReleaseInfo + 2);
		std::vector<char> bufferBuildInfo;
		bufferBuildInfo.resize(bytesNeededBuildInfo + 2);
		CheckError(nullptr,libprimes_getlibraryversion(&nMajor, &nMinor, &nMicro, bytesNeededPreReleaseInfo + 2, &bytesWrittenPreReleaseInfo, &bufferPreReleaseInfo[0], bytesNeededBuildInfo + 2, &bytesWrittenBuildInfo, &bufferBuildInfo[0]));
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
		CheckError(nullptr,libprimes_createfactorizationcalculator(&hInstance));
		return std::make_shared<CFactorizationCalculator>(this, hInstance);
	}
	
	/**
	* CWrapper::CreateSieveCalculator - Creates a new SieveCalculator instance
	* @return New SieveCalculator instance
	*/
	inline PSieveCalculator CWrapper::CreateSieveCalculator()
	{
		LibPrimesHandle hInstance = nullptr;
		CheckError(nullptr,libprimes_createsievecalculator(&hInstance));
		return std::make_shared<CSieveCalculator>(this, hInstance);
	}
	
	/**
	* CWrapper::SetJournal - Handles Library Journaling
	* @param[in] sFileName - Journal FileName
	*/
	inline void CWrapper::SetJournal(const std::string & sFileName)
	{
		CheckError(nullptr,libprimes_setjournal(sFileName.c_str()));
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
	

	
	/**
	 * Method definitions for class CBase
	 */
	
	/**
	 * Method definitions for class CCalculator
	 */
	
	LibPrimes_uint64 CCalculator::GetValue()
	{
		LibPrimes_uint64 resultValue = 0;
		CheckError(libprimes_calculator_getvalue(m_pHandle, &resultValue));
		return resultValue;
	}
	
	void CCalculator::SetValue(const LibPrimes_uint64 nValue)
	{
		CheckError(libprimes_calculator_setvalue(m_pHandle, nValue));
	}
	
	void CCalculator::Calculate()
	{
		CheckError(libprimes_calculator_calculate(m_pHandle));
	}
	
	void CCalculator::SetProgressCallback(const ProgressCallback pProgressCallback)
	{
		CheckError(libprimes_calculator_setprogresscallback(m_pHandle, pProgressCallback));
	}
	
	/**
	 * Method definitions for class CFactorizationCalculator
	 */
	
	void CFactorizationCalculator::GetPrimeFactors(std::vector<sPrimeFactor> & PrimeFactorsBuffer)
	{
		LibPrimes_uint64 elementsNeededPrimeFactors = 0;
		LibPrimes_uint64 elementsWrittenPrimeFactors = 0;
		CheckError(libprimes_factorizationcalculator_getprimefactors(m_pHandle, 0, &elementsNeededPrimeFactors, nullptr));
		PrimeFactorsBuffer.resize((size_t) elementsNeededPrimeFactors);
		CheckError(libprimes_factorizationcalculator_getprimefactors(m_pHandle, elementsNeededPrimeFactors, &elementsWrittenPrimeFactors, PrimeFactorsBuffer.data()));
	}
	
	/**
	 * Method definitions for class CSieveCalculator
	 */
	
	void CSieveCalculator::GetPrimes(std::vector<LibPrimes_uint64> & PrimesBuffer)
	{
		LibPrimes_uint64 elementsNeededPrimes = 0;
		LibPrimes_uint64 elementsWrittenPrimes = 0;
		CheckError(libprimes_sievecalculator_getprimes(m_pHandle, 0, &elementsNeededPrimes, nullptr));
		PrimesBuffer.resize((size_t) elementsNeededPrimes);
		CheckError(libprimes_sievecalculator_getprimes(m_pHandle, elementsNeededPrimes, &elementsWrittenPrimes, PrimesBuffer.data()));
	}

} // namespace LibPrimes

#endif // __LIBPRIMES_CPPHEADER_IMPLICIT_CPP

