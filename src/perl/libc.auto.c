/*
 * This file was generated automatically by ExtUtils::ParseXS version 3.34 from the
 * contents of LibC.xs. Do not edit this file, edit LibC.xs instead.
 *
 *    ANY CHANGES MADE HERE WILL BE LOST!
 *
 */

/***********************************************************************************************************************************
C to Perl Interface

The following C types are mapped by the current typemap:

'AV *', 'Boolean', 'CV *', 'FILE *', 'FileHandle', 'HV *', 'I16', 'I32', 'I8', 'IV', 'InOutStream', 'InputStream', 'NV',
'OutputStream', 'PerlIO *', 'Result', 'STRLEN', 'SV *', 'SVREF', 'SysRet', 'SysRetLong', 'Time_t *', 'U16', 'U32', 'U8', 'UV',
'bool', 'bool_t', 'caddr_t', 'char', 'char *', 'char **', 'const char *', 'double', 'float', 'int', 'long', 'short', 'size_t',
'ssize_t', 'time_t', 'unsigned', 'unsigned char', 'unsigned char *', 'unsigned int', 'unsigned long', 'unsigned long *',
'unsigned short', 'void *', 'wchar_t', 'wchar_t *'
***********************************************************************************************************************************/
#include "build.auto.h"

#define PERL_NO_GET_CONTEXT

/***********************************************************************************************************************************
Perl includes

Order is critical here so don't change it.
***********************************************************************************************************************************/
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 8 || (__GNUC_MINOR__ == 8 && __GNUC_PATCHLEVEL__ >= 0)))
    #define WARNING_MAYBE_INITIALIZED 1
#elif __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ >= 0)))
    #define WARNING_INITIALIZED 1
#endif

#if WARNING_MAYBE_INITIALIZED
    #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#elif WARNING_INITIALIZED
    #pragma GCC diagnostic ignored "-Wuninitialized"
#endif

#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"

#include <XSUB.h>
#include <EXTERN.h>
#include <perl.h>

#if WARNING_MAYBE_INITIALIZED
    #pragma GCC diagnostic warning "-Wmaybe-uninitialized"
#elif WARNING_INITIALIZED
    #pragma GCC diagnostic warning "-Wuninitialized"
#endif

/***********************************************************************************************************************************
C includes

These includes are from the src directory.  There is no Perl-specific code in them.
***********************************************************************************************************************************/
#include "common/crypto/common.h"
#include "common/error.h"
#include "common/lock.h"
#include "config/config.h"
#include "config/define.h"
#include "config/load.h"
#include "config/parse.h"
#include "perl/config.h"
#include "postgres/pageChecksum.h"
#include "storage/driver/posix/storage.h"

/***********************************************************************************************************************************
Helper macros
***********************************************************************************************************************************/
#include "LibC.h"

/***********************************************************************************************************************************
XSH includes

These includes define data structures that are required for the C to Perl interface but are not part of the regular C source.
***********************************************************************************************************************************/
#include "xs/crypto/cipherBlock.xsh"
#include "xs/crypto/hash.xsh"
#include "xs/common/encode.xsh"

/***********************************************************************************************************************************
Module definition
***********************************************************************************************************************************/
#ifndef PERL_UNUSED_VAR
#  define PERL_UNUSED_VAR(var) if (0) var = var
#endif

#ifndef dVAR
#  define dVAR		dNOOP
#endif


/* This stuff is not part of the API! You have been warned. */
#ifndef PERL_VERSION_DECIMAL
#  define PERL_VERSION_DECIMAL(r,v,s) (r*1000000 + v*1000 + s)
#endif
#ifndef PERL_DECIMAL_VERSION
#  define PERL_DECIMAL_VERSION \
	  PERL_VERSION_DECIMAL(PERL_REVISION,PERL_VERSION,PERL_SUBVERSION)
#endif
#ifndef PERL_VERSION_GE
#  define PERL_VERSION_GE(r,v,s) \
	  (PERL_DECIMAL_VERSION >= PERL_VERSION_DECIMAL(r,v,s))
#endif
#ifndef PERL_VERSION_LE
#  define PERL_VERSION_LE(r,v,s) \
	  (PERL_DECIMAL_VERSION <= PERL_VERSION_DECIMAL(r,v,s))
#endif

/* XS_INTERNAL is the explicit static-linkage variant of the default
 * XS macro.
 *
 * XS_EXTERNAL is the same as XS_INTERNAL except it does not include
 * "STATIC", ie. it exports XSUB symbols. You probably don't want that
 * for anything but the BOOT XSUB.
 *
 * See XSUB.h in core!
 */


/* TODO: This might be compatible further back than 5.10.0. */
#if PERL_VERSION_GE(5, 10, 0) && PERL_VERSION_LE(5, 15, 1)
#  undef XS_EXTERNAL
#  undef XS_INTERNAL
#  if defined(__CYGWIN__) && defined(USE_DYNAMIC_LOADING)
#    define XS_EXTERNAL(name) __declspec(dllexport) XSPROTO(name)
#    define XS_INTERNAL(name) STATIC XSPROTO(name)
#  endif
#  if defined(__SYMBIAN32__)
#    define XS_EXTERNAL(name) EXPORT_C XSPROTO(name)
#    define XS_INTERNAL(name) EXPORT_C STATIC XSPROTO(name)
#  endif
#  ifndef XS_EXTERNAL
#    if defined(HASATTRIBUTE_UNUSED) && !defined(__cplusplus)
#      define XS_EXTERNAL(name) void name(pTHX_ CV* cv __attribute__unused__)
#      define XS_INTERNAL(name) STATIC void name(pTHX_ CV* cv __attribute__unused__)
#    else
#      ifdef __cplusplus
#        define XS_EXTERNAL(name) extern "C" XSPROTO(name)
#        define XS_INTERNAL(name) static XSPROTO(name)
#      else
#        define XS_EXTERNAL(name) XSPROTO(name)
#        define XS_INTERNAL(name) STATIC XSPROTO(name)
#      endif
#    endif
#  endif
#endif

/* perl >= 5.10.0 && perl <= 5.15.1 */


/* The XS_EXTERNAL macro is used for functions that must not be static
 * like the boot XSUB of a module. If perl didn't have an XS_EXTERNAL
 * macro defined, the best we can do is assume XS is the same.
 * Dito for XS_INTERNAL.
 */
#ifndef XS_EXTERNAL
#  define XS_EXTERNAL(name) XS(name)
#endif
#ifndef XS_INTERNAL
#  define XS_INTERNAL(name) XS(name)
#endif

/* Now, finally, after all this mess, we want an ExtUtils::ParseXS
 * internal macro that we're free to redefine for varying linkage due
 * to the EXPORT_XSUB_SYMBOLS XS keyword. This is internal, use
 * XS_EXTERNAL(name) or XS_INTERNAL(name) in your code if you need to!
 */

#undef XS_EUPXS
#if defined(PERL_EUPXS_ALWAYS_EXPORT)
#  define XS_EUPXS(name) XS_EXTERNAL(name)
#else
   /* default to internal */
#  define XS_EUPXS(name) XS_INTERNAL(name)
#endif

#ifndef PERL_ARGS_ASSERT_CROAK_XS_USAGE
#define PERL_ARGS_ASSERT_CROAK_XS_USAGE assert(cv); assert(params)

/* prototype to pass -Wmissing-prototypes */
STATIC void
S_croak_xs_usage(const CV *const cv, const char *const params);

STATIC void
S_croak_xs_usage(const CV *const cv, const char *const params)
{
    const GV *const gv = CvGV(cv);

    PERL_ARGS_ASSERT_CROAK_XS_USAGE;

    if (gv) {
        const char *const gvname = GvNAME(gv);
        const HV *const stash = GvSTASH(gv);
        const char *const hvname = stash ? HvNAME(stash) : NULL;

        if (hvname)
	    Perl_croak_nocontext("Usage: %s::%s(%s)", hvname, gvname, params);
        else
	    Perl_croak_nocontext("Usage: %s(%s)", gvname, params);
    } else {
        /* Pants. I don't think that it should be possible to get here. */
	Perl_croak_nocontext("Usage: CODE(0x%" UVxf ")(%s)", PTR2UV(cv), params);
    }
}
#undef  PERL_ARGS_ASSERT_CROAK_XS_USAGE

#define croak_xs_usage        S_croak_xs_usage

#endif

/* NOTE: the prototype of newXSproto() is different in versions of perls,
 * so we define a portable version of newXSproto()
 */
#ifdef newXS_flags
#define newXSproto_portable(name, c_impl, file, proto) newXS_flags(name, c_impl, file, proto, 0)
#else
#define newXSproto_portable(name, c_impl, file, proto) (PL_Sv=(SV*)newXS(name, c_impl, file), sv_setpv(PL_Sv, proto), (CV*)PL_Sv)
#endif /* !defined(newXS_flags) */

#if PERL_VERSION_LE(5, 21, 5)
#  define newXS_deffile(a,b) Perl_newXS(aTHX_ a,b,file)
#else
#  define newXS_deffile(a,b) Perl_newXS_deffile(aTHX_ a,b)
#endif


XS_EUPXS(XS_pgBackRest__LibC_libcUvSize); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_libcUvSize)
{
    dVAR; dXSARGS;
    if (items != 0)
       croak_xs_usage(cv,  "");
    {
	I32	RETVAL;
	dXSTARG;
    RETVAL = UVSIZE;
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


/* INCLUDE:  Including 'xs/common/encode.xs' from 'LibC.xs' */


/* INCLUDE:  Including 'xs/common/lock.xs' from 'xs/common/encode.xs' */


/* INCLUDE:  Including 'xs/config/config.xs' from 'xs/common/lock.xs' */


/* INCLUDE:  Including 'xs/config/configTest.xs' from 'xs/config/config.xs' */


/* INCLUDE:  Including 'xs/config/define.xs' from 'xs/config/configTest.xs' */


/* INCLUDE:  Including 'xs/crypto/cipherBlock.xs' from 'xs/config/define.xs' */


/* INCLUDE:  Including 'xs/crypto/hash.xs' from 'xs/crypto/cipherBlock.xs' */


/* INCLUDE:  Including 'xs/crypto/random.xs' from 'xs/crypto/hash.xs' */


/* INCLUDE:  Including 'xs/postgres/pageChecksum.xs' from 'xs/crypto/random.xs' */


/* INCLUDE:  Including 'xs/storage/storage.xs' from 'xs/postgres/pageChecksum.xs' */


XS_EUPXS(XS_pgBackRest__LibC_storageDriverPosixPathRemove); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_storageDriverPosixPathRemove)
{
    dVAR; dXSARGS;
    if (items != 3)
       croak_xs_usage(cv,  "path, errorOnMissing, recurse");
    {
	const char *	path = (const char *)SvPV_nolen(ST(0))
;
	bool	errorOnMissing = (bool)SvTRUE(ST(1))
;
	bool	recurse = (bool)SvTRUE(ST(2))
;
    MEM_CONTEXT_XS_TEMP_BEGIN()
    {
        storagePathRemoveP(
            storageDriverPosixNew(strNew("/"), 0640, 750, true, NULL), strNew(path), .errorOnMissing = errorOnMissing,
            .recurse = recurse);
    }
    MEM_CONTEXT_XS_TEMP_END();
    }
    XSRETURN_EMPTY;
}


/* INCLUDE: Returning to 'xs/postgres/pageChecksum.xs' from 'xs/storage/storage.xs' */


XS_EUPXS(XS_pgBackRest__LibC_pageChecksum); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_pageChecksum)
{
    dVAR; dXSARGS;
    if (items != 3)
       croak_xs_usage(cv,  "page, blockNo, pageSize");
    {
	const char *	page = (const char *)SvPV_nolen(ST(0))
;
	U32	blockNo = (unsigned long)SvUV(ST(1))
;
	U32	pageSize = (unsigned long)SvUV(ST(2))
;
	U16	RETVAL;
	dXSTARG;
    RETVAL = 0;

    ERROR_XS_BEGIN()
    {
        RETVAL = pageChecksum(
            (const unsigned char *)page, blockNo, pageSize);
    }
    ERROR_XS_END();
	XSprePUSH; PUSHu((UV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_pgBackRest__LibC_pageChecksumTest); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_pageChecksumTest)
{
    dVAR; dXSARGS;
    if (items != 5)
       croak_xs_usage(cv,  "page, blockNo, pageSize, ignoreWalId, ignoreWalOffset");
    {
	const char *	page = (const char *)SvPV_nolen(ST(0))
;
	U32	blockNo = (unsigned long)SvUV(ST(1))
;
	U32	pageSize = (unsigned long)SvUV(ST(2))
;
	U32	ignoreWalId = (unsigned long)SvUV(ST(3))
;
	U32	ignoreWalOffset = (unsigned long)SvUV(ST(4))
;
	bool	RETVAL;
    RETVAL = false;

    ERROR_XS_BEGIN()
    {
        RETVAL = pageChecksumTest(
            (const unsigned char *)page, blockNo, pageSize, ignoreWalId, ignoreWalOffset);
    }
    ERROR_XS_END();
	ST(0) = boolSV(RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_pgBackRest__LibC_pageChecksumBufferTest); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_pageChecksumBufferTest)
{
    dVAR; dXSARGS;
    if (items != 6)
       croak_xs_usage(cv,  "pageBuffer, pageBufferSize, blockNoBegin, pageSize, ignoreWalId, ignoreWalOffset");
    {
	const char *	pageBuffer = (const char *)SvPV_nolen(ST(0))
;
	U32	pageBufferSize = (unsigned long)SvUV(ST(1))
;
	U32	blockNoBegin = (unsigned long)SvUV(ST(2))
;
	U32	pageSize = (unsigned long)SvUV(ST(3))
;
	U32	ignoreWalId = (unsigned long)SvUV(ST(4))
;
	U32	ignoreWalOffset = (unsigned long)SvUV(ST(5))
;
	bool	RETVAL;
    RETVAL = false;

    ERROR_XS_BEGIN()
    {
        RETVAL = pageChecksumBufferTest(
            (const unsigned char *)pageBuffer, pageBufferSize, blockNoBegin, pageSize, ignoreWalId, ignoreWalOffset);
    }
    ERROR_XS_END();
	ST(0) = boolSV(RETVAL);
    }
    XSRETURN(1);
}


/* INCLUDE: Returning to 'xs/crypto/random.xs' from 'xs/postgres/pageChecksum.xs' */


XS_EUPXS(XS_pgBackRest__LibC_cryptoRandomBytes); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_cryptoRandomBytes)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "size");
    {
	I32	size = (I32)SvIV(ST(0))
;
	SV *	RETVAL;
    RETVAL = newSV(size);
    SvPOK_only(RETVAL);

    cryptoRandomBytes((unsigned char *)SvPV_nolen(RETVAL), size);

    SvCUR_set(RETVAL, size);
	RETVAL = sv_2mortal(RETVAL);
	ST(0) = RETVAL;
    }
    XSRETURN(1);
}


/* INCLUDE: Returning to 'xs/crypto/hash.xs' from 'xs/crypto/random.xs' */


XS_EUPXS(XS_pgBackRest__LibC__Crypto__Hash_new); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC__Crypto__Hash_new)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "class, type");
    {
	const char *	class = (const char *)SvPV_nolen(ST(0))
;
	const char *	type = (const char *)SvPV_nolen(ST(1))
;
	pgBackRest__LibC__Crypto__Hash	RETVAL;
    RETVAL = NULL;

    // Don't warn when class param is used
    (void)class;

    MEM_CONTEXT_XS_NEW_BEGIN("cryptoHashXs")
    {
        RETVAL = memNew(sizeof(CryptoHashXs));
        RETVAL->memContext = MEM_COMTEXT_XS();
        RETVAL->pxPayload = cryptoHashNew(strNew(type));
    }
    MEM_CONTEXT_XS_NEW_END();
	{
	    SV * RETVALSV;
	    RETVALSV = sv_newmortal();
	    sv_setref_pv(RETVALSV, "pgBackRest::LibC::Crypto::Hash", (void*)RETVAL);
	    ST(0) = RETVALSV;
	}
    }
    XSRETURN(1);
}


XS_EUPXS(XS_pgBackRest__LibC__Crypto__Hash_process); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC__Crypto__Hash_process)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "self, message");
    {
	pgBackRest__LibC__Crypto__Hash	self;
	SV *	message = ST(1)
;

	if (SvROK(ST(0)) && sv_derived_from(ST(0), "pgBackRest::LibC::Crypto::Hash")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    self = INT2PTR(pgBackRest__LibC__Crypto__Hash,tmp);
	}
	else
	    Perl_croak_nocontext("%s: %s is not of type %s",
			"pgBackRest::LibC::Crypto::Hash::process",
			"self", "pgBackRest::LibC::Crypto::Hash")
;
    MEM_CONTEXT_XS_TEMP_BEGIN()
    {
        STRLEN messageSize;
        const void *messagePtr = SvPV(message, messageSize);

        if (messageSize > 0)
            ioFilterProcessIn(self->pxPayload, BUF(messagePtr, messageSize));
    }
    MEM_CONTEXT_XS_TEMP_END();
    }
    XSRETURN_EMPTY;
}


XS_EUPXS(XS_pgBackRest__LibC__Crypto__Hash_result); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC__Crypto__Hash_result)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "self");
    {
	pgBackRest__LibC__Crypto__Hash	self;
	SV *	RETVAL;

	if (SvROK(ST(0)) && sv_derived_from(ST(0), "pgBackRest::LibC::Crypto::Hash")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    self = INT2PTR(pgBackRest__LibC__Crypto__Hash,tmp);
	}
	else
	    Perl_croak_nocontext("%s: %s is not of type %s",
			"pgBackRest::LibC::Crypto::Hash::result",
			"self", "pgBackRest::LibC::Crypto::Hash")
;
    RETVAL = NULL;

    MEM_CONTEXT_XS_TEMP_BEGIN()
    {
        const String *hash = varStr(ioFilterResult(self->pxPayload));

        RETVAL = newSV(strSize(hash));
        SvPOK_only(RETVAL);
        strcpy((char *)SvPV_nolen(RETVAL), strPtr(hash));
        SvCUR_set(RETVAL, strSize(hash));
    }
    MEM_CONTEXT_XS_TEMP_END();
	RETVAL = sv_2mortal(RETVAL);
	ST(0) = RETVAL;
    }
    XSRETURN(1);
}


XS_EUPXS(XS_pgBackRest__LibC__Crypto__Hash_DESTROY); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC__Crypto__Hash_DESTROY)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "self");
    {
	pgBackRest__LibC__Crypto__Hash	self;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    self = INT2PTR(pgBackRest__LibC__Crypto__Hash,tmp);
	}
	else
	    Perl_croak_nocontext("%s: %s is not a reference",
			"pgBackRest::LibC::Crypto::Hash::DESTROY",
			"self")
;
    MEM_CONTEXT_XS_DESTROY(self->memContext);
    }
    XSRETURN_EMPTY;
}


XS_EUPXS(XS_pgBackRest__LibC_cryptoHashOne); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_cryptoHashOne)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "type, message");
    {
	const char *	type = (const char *)SvPV_nolen(ST(0))
;
	SV *	message = ST(1)
;
	SV *	RETVAL;
    RETVAL = NULL;

    MEM_CONTEXT_XS_TEMP_BEGIN()
    {
        STRLEN messageSize;
        const void *messagePtr = SvPV(message, messageSize);

        String *hash = bufHex(cryptoHashOne(strNew(type), BUF(messagePtr, messageSize)));

        RETVAL = newSV(strSize(hash));
        SvPOK_only(RETVAL);
        strcpy((char *)SvPV_nolen(RETVAL), strPtr(hash));
        SvCUR_set(RETVAL, strSize(hash));
    }
    MEM_CONTEXT_XS_TEMP_END();
	RETVAL = sv_2mortal(RETVAL);
	ST(0) = RETVAL;
    }
    XSRETURN(1);
}


/* INCLUDE: Returning to 'xs/crypto/cipherBlock.xs' from 'xs/crypto/hash.xs' */


XS_EUPXS(XS_pgBackRest__LibC__Cipher__Block_new); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC__Cipher__Block_new)
{
    dVAR; dXSARGS;
    if (items < 5 || items > 6)
       croak_xs_usage(cv,  "class, mode, type, key, keySize, digest = NULL");
    {
	const char *	class = (const char *)SvPV_nolen(ST(0))
;
	U32	mode = (unsigned long)SvUV(ST(1))
;
	const char *	type = (const char *)SvPV_nolen(ST(2))
;
	unsigned char *	key = (unsigned char *)SvPV_nolen(ST(3))
;
	I32	keySize = (I32)SvIV(ST(4))
;
	const char *	digest;
	pgBackRest__LibC__Cipher__Block	RETVAL;

	if (items < 6)
	    digest = NULL;
	else {
	    digest = (const char *)SvPV_nolen(ST(5))
;
	}
    RETVAL = NULL;

    CHECK(type != NULL);
    CHECK(key != NULL);
    CHECK(keySize != 0);

    // Not much point to this but it keeps the var from being unused
    if (strcmp(class, PACKAGE_NAME_LIBC "::Cipher::Block") != 0)
        croak("unexpected class name '%s'", class);

    MEM_CONTEXT_XS_NEW_BEGIN("cipherBlockXs")
    {
        RETVAL = memNew(sizeof(CipherBlockXs));
        RETVAL->memContext = MEM_COMTEXT_XS();

        RETVAL->pxPayload = cipherBlockNew(mode, cipherType(STR(type)), BUF(key, keySize), digest == NULL ? NULL : STR(digest));
    }
    MEM_CONTEXT_XS_NEW_END();
	{
	    SV * RETVALSV;
	    RETVALSV = sv_newmortal();
	    sv_setref_pv(RETVALSV, "pgBackRest::LibC::Cipher::Block", (void*)RETVAL);
	    ST(0) = RETVALSV;
	}
    }
    XSRETURN(1);
}


XS_EUPXS(XS_pgBackRest__LibC__Cipher__Block_process); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC__Cipher__Block_process)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "self, source");
    {
	pgBackRest__LibC__Cipher__Block	self;
	SV *	source = ST(1)
;
	SV *	RETVAL;

	if (SvROK(ST(0)) && sv_derived_from(ST(0), "pgBackRest::LibC::Cipher::Block")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    self = INT2PTR(pgBackRest__LibC__Cipher__Block,tmp);
	}
	else
	    Perl_croak_nocontext("%s: %s is not of type %s",
			"pgBackRest::LibC::Cipher::Block::process",
			"self", "pgBackRest::LibC::Cipher::Block")
;
    RETVAL = NULL;

    MEM_CONTEXT_XS_BEGIN(self->memContext)
    {
        STRLEN tSize;
        const unsigned char *sourcePtr = (const unsigned char *)SvPV(source, tSize);

        RETVAL = NEWSV(0, ioBufferSize());
        SvPOK_only(RETVAL);

        if (tSize > 0)
        {
            size_t outBufferUsed = 0;

            do
            {
                SvGROW(RETVAL, outBufferUsed + ioBufferSize());
                Buffer *outBuffer = bufNewUseC((unsigned char *)SvPV_nolen(RETVAL) + outBufferUsed, ioBufferSize());

                ioFilterProcessInOut(self->pxPayload, BUF(sourcePtr, tSize), outBuffer);
                outBufferUsed += bufUsed(outBuffer);
            }
            while (ioFilterInputSame(self->pxPayload));

            SvCUR_set(RETVAL, outBufferUsed);
        }
        else
            SvCUR_set(RETVAL, 0);
    }
    MEM_CONTEXT_XS_END();
	RETVAL = sv_2mortal(RETVAL);
	ST(0) = RETVAL;
    }
    XSRETURN(1);
}


XS_EUPXS(XS_pgBackRest__LibC__Cipher__Block_flush); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC__Cipher__Block_flush)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "self");
    {
	pgBackRest__LibC__Cipher__Block	self;
	SV *	RETVAL;

	if (SvROK(ST(0)) && sv_derived_from(ST(0), "pgBackRest::LibC::Cipher::Block")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    self = INT2PTR(pgBackRest__LibC__Cipher__Block,tmp);
	}
	else
	    Perl_croak_nocontext("%s: %s is not of type %s",
			"pgBackRest::LibC::Cipher::Block::flush",
			"self", "pgBackRest::LibC::Cipher::Block")
;
    RETVAL = NULL;

    MEM_CONTEXT_XS_BEGIN(self->memContext)
    {
        RETVAL = NEWSV(0, ioBufferSize());
        SvPOK_only(RETVAL);

        size_t outBufferUsed = 0;

        do
        {
            SvGROW(RETVAL, outBufferUsed + ioBufferSize());
            Buffer *outBuffer = bufNewUseC((unsigned char *)SvPV_nolen(RETVAL) + outBufferUsed, ioBufferSize());

            ioFilterProcessInOut(self->pxPayload, NULL, outBuffer);
            outBufferUsed += bufUsed(outBuffer);
        }
        while (!ioFilterDone(self->pxPayload));

        SvCUR_set(RETVAL, outBufferUsed);
    }
    MEM_CONTEXT_XS_END();
	RETVAL = sv_2mortal(RETVAL);
	ST(0) = RETVAL;
    }
    XSRETURN(1);
}


XS_EUPXS(XS_pgBackRest__LibC__Cipher__Block_DESTROY); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC__Cipher__Block_DESTROY)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "self");
    {
	pgBackRest__LibC__Cipher__Block	self;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    self = INT2PTR(pgBackRest__LibC__Cipher__Block,tmp);
	}
	else
	    Perl_croak_nocontext("%s: %s is not a reference",
			"pgBackRest::LibC::Cipher::Block::DESTROY",
			"self")
;
    MEM_CONTEXT_XS_DESTROY(self->memContext);
    }
    XSRETURN_EMPTY;
}


/* INCLUDE: Returning to 'xs/config/define.xs' from 'xs/crypto/cipherBlock.xs' */


XS_EUPXS(XS_pgBackRest__LibC_cfgCommandId); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_cfgCommandId)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "commandName");
    {
	const char *	commandName = (const char *)SvPV_nolen(ST(0))
;
	I32	RETVAL;
	dXSTARG;
    RETVAL = 0;

    ERROR_XS_BEGIN()
    {
        RETVAL = cfgCommandId(commandName);
    }
    ERROR_XS_END();
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_pgBackRest__LibC_cfgOptionId); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_cfgOptionId)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "optionName");
    {
	const char *	optionName = (const char *)SvPV_nolen(ST(0))
;
	I32	RETVAL;
	dXSTARG;
    RETVAL = 0;

    ERROR_XS_BEGIN()
    {
        RETVAL = cfgOptionId(optionName);
    }
    ERROR_XS_END();
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_pgBackRest__LibC_cfgDefOptionDefault); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_cfgDefOptionDefault)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "commandId, optionId");
    {
	U32	commandId = (unsigned long)SvUV(ST(0))
;
	U32	optionId = (unsigned long)SvUV(ST(1))
;
	const char *	RETVAL;
	dXSTARG;
    RETVAL = NULL;

    ERROR_XS_BEGIN()
    {
        RETVAL = cfgDefOptionDefault(cfgCommandDefIdFromId(commandId), cfgOptionDefIdFromId(optionId));
    }
    ERROR_XS_END();
	sv_setpv(TARG, RETVAL); XSprePUSH; PUSHTARG;
    }
    XSRETURN(1);
}


XS_EUPXS(XS_pgBackRest__LibC_cfgDefOptionPrefix); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_cfgDefOptionPrefix)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "optionId");
    {
	U32	optionId = (unsigned long)SvUV(ST(0))
;
	const char *	RETVAL;
	dXSTARG;
    RETVAL = NULL;

    ERROR_XS_BEGIN()
    {
        RETVAL = cfgDefOptionPrefix(cfgOptionDefIdFromId(optionId));
    }
    ERROR_XS_END();
	sv_setpv(TARG, RETVAL); XSprePUSH; PUSHTARG;
    }
    XSRETURN(1);
}


XS_EUPXS(XS_pgBackRest__LibC_cfgDefOptionSecure); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_cfgDefOptionSecure)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "optionId");
    {
	U32	optionId = (unsigned long)SvUV(ST(0))
;
	bool	RETVAL;
    RETVAL = false;

    ERROR_XS_BEGIN()
    {
        RETVAL = cfgDefOptionSecure(cfgOptionDefIdFromId(optionId));
    }
    ERROR_XS_END();
	ST(0) = boolSV(RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_pgBackRest__LibC_cfgDefOptionType); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_cfgDefOptionType)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "optionId");
    {
	U32	optionId = (unsigned long)SvUV(ST(0))
;
	I32	RETVAL;
	dXSTARG;
    RETVAL = 0;

    ERROR_XS_BEGIN()
    {
        RETVAL = cfgDefOptionType(cfgOptionDefIdFromId(optionId));
    }
    ERROR_XS_END();
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_pgBackRest__LibC_cfgDefOptionValid); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_cfgDefOptionValid)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "commandId, optionId");
    {
	U32	commandId = (unsigned long)SvUV(ST(0))
;
	U32	optionId = (unsigned long)SvUV(ST(1))
;
	bool	RETVAL;
    RETVAL = false;

    ERROR_XS_BEGIN()
    {
        RETVAL = cfgDefOptionValid(cfgCommandDefIdFromId(commandId), cfgOptionDefIdFromId(optionId));
    }
    ERROR_XS_END();
	ST(0) = boolSV(RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_pgBackRest__LibC_cfgOptionTotal); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_cfgOptionTotal)
{
    dVAR; dXSARGS;
    if (items != 0)
       croak_xs_usage(cv,  "");
    {
	U32	RETVAL;
	dXSTARG;
    RETVAL = CFG_OPTION_TOTAL;
	XSprePUSH; PUSHu((UV)RETVAL);
    }
    XSRETURN(1);
}


/* INCLUDE: Returning to 'xs/config/configTest.xs' from 'xs/config/define.xs' */


XS_EUPXS(XS_pgBackRest__LibC_cfgParseTest); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_cfgParseTest)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "backrestBin, parseParam");
    {
	const char *	backrestBin = (const char *)SvPV_nolen(ST(0))
;
	const char *	parseParam = (const char *)SvPV_nolen(ST(1))
;
	SV *	RETVAL;
    RETVAL = NULL;

    ERROR_XS_BEGIN()
    {
        // This should run in a temp context but for some reason getopt_long gets upset when if gets called again after the previous
        // arg list being freed.  So, this is a memory leak but it is only used for testing, not production.
        StringList *paramList = strLstNewSplitZ(strCat(strNew("pgbackrest|"), parseParam), "|");

        // Don't use cfgLoad() because it has a lot of side effects that we don't want
        configParse(strLstSize(paramList), strLstPtr(paramList), false);
        cfgExeSet(strNew(backrestBin));
        cfgLoadUpdateOption();

        String *result = perlOptionJson();

        RETVAL = newSV(strSize(result));
        SvPOK_only(RETVAL);

        strcpy(SvPV_nolen(RETVAL), strPtr(result));
        SvCUR_set(RETVAL, strSize(result));
    }
    ERROR_XS_END()
	RETVAL = sv_2mortal(RETVAL);
	ST(0) = RETVAL;
    }
    XSRETURN(1);
}


/* INCLUDE: Returning to 'xs/config/config.xs' from 'xs/config/configTest.xs' */


XS_EUPXS(XS_pgBackRest__LibC_cfgCommandName); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_cfgCommandName)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "commandId");
    {
	U32	commandId = (unsigned long)SvUV(ST(0))
;
	const char *	RETVAL;
	dXSTARG;

	RETVAL = cfgCommandName(commandId);
	sv_setpv(TARG, RETVAL); XSprePUSH; PUSHTARG;
    }
    XSRETURN(1);
}


XS_EUPXS(XS_pgBackRest__LibC_cfgOptionIndex); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_cfgOptionIndex)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "optionId");
    {
	U32	optionId = (unsigned long)SvUV(ST(0))
;
	I32	RETVAL;
	dXSTARG;

	RETVAL = cfgOptionIndex(optionId);
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_pgBackRest__LibC_cfgOptionIndexTotal); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_cfgOptionIndexTotal)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "optionId");
    {
	U32	optionId = (unsigned long)SvUV(ST(0))
;
	I32	RETVAL;
	dXSTARG;

	RETVAL = cfgOptionIndexTotal(optionId);
	XSprePUSH; PUSHi((IV)RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_pgBackRest__LibC_cfgOptionName); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_cfgOptionName)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "optionId");
    {
	U32	optionId = (unsigned long)SvUV(ST(0))
;
	const char *	RETVAL;
	dXSTARG;

	RETVAL = cfgOptionName(optionId);
	sv_setpv(TARG, RETVAL); XSprePUSH; PUSHTARG;
    }
    XSRETURN(1);
}


/* INCLUDE: Returning to 'xs/common/lock.xs' from 'xs/config/config.xs' */


XS_EUPXS(XS_pgBackRest__LibC_lockAcquire); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_lockAcquire)
{
    dVAR; dXSARGS;
    if (items != 5)
       croak_xs_usage(cv,  "lockPath, command, stanza, lockTimeout, failOnNoLock");
    {
	const char *	lockPath = (const char *)SvPV_nolen(ST(0))
;
	const char *	command = (const char *)SvPV_nolen(ST(1))
;
	const char *	stanza = (const char *)SvPV_nolen(ST(2))
;
	double	lockTimeout = (double)SvNV(ST(3))
;
	bool	failOnNoLock = (bool)SvTRUE(ST(4))
;
	bool	RETVAL;
    RETVAL = false;

    MEM_CONTEXT_XS_TEMP_BEGIN()
    {
        // Set the command so we can get the correct lock type to use
        cfgCommandSet(cfgCommandId(command));

        // Attempt to acquire the lock
        if (cfgLockRequired())
            RETVAL = lockAcquire(strNew(lockPath), strNew(stanza), cfgLockType(), (TimeMSec)(lockTimeout * 1000), failOnNoLock);
    }
    MEM_CONTEXT_XS_TEMP_END();
	ST(0) = boolSV(RETVAL);
    }
    XSRETURN(1);
}


XS_EUPXS(XS_pgBackRest__LibC_lockRelease); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_lockRelease)
{
    dVAR; dXSARGS;
    if (items != 1)
       croak_xs_usage(cv,  "failOnNoLock");
    {
	bool	failOnNoLock = (bool)SvTRUE(ST(0))
;
	bool	RETVAL;
    RETVAL = false;

    MEM_CONTEXT_XS_TEMP_BEGIN()
    {
        RETVAL = lockRelease(failOnNoLock);
    }
    MEM_CONTEXT_XS_TEMP_END();
	ST(0) = boolSV(RETVAL);
    }
    XSRETURN(1);
}


/* INCLUDE: Returning to 'xs/common/encode.xs' from 'xs/common/lock.xs' */


XS_EUPXS(XS_pgBackRest__LibC_encodeToStr); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_encodeToStr)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "encodeType, source");
    {
	int	encodeType = (int)SvIV(ST(0))
;
	SV *	source = ST(1)
;
	SV *	RETVAL;
    RETVAL = NULL;

    STRLEN sourceSize;
    unsigned char *sourcePtr = (unsigned char *)SvPV(source, sourceSize);

    ERROR_XS_BEGIN()
    {
        RETVAL = newSV(encodeToStrSize(encodeType, sourceSize));
        SvPOK_only(RETVAL);

        encodeToStr(encodeType, sourcePtr, sourceSize, (char *)SvPV_nolen(RETVAL));
        SvCUR_set(RETVAL, encodeToStrSize(encodeType, sourceSize));
    }
    ERROR_XS_END();
	RETVAL = sv_2mortal(RETVAL);
	ST(0) = RETVAL;
    }
    XSRETURN(1);
}


XS_EUPXS(XS_pgBackRest__LibC_decodeToBin); /* prototype to pass -Wmissing-prototypes */
XS_EUPXS(XS_pgBackRest__LibC_decodeToBin)
{
    dVAR; dXSARGS;
    if (items != 2)
       croak_xs_usage(cv,  "encodeType, source");
    {
	int	encodeType = (int)SvIV(ST(0))
;
	const char *	source = (const char *)SvPV_nolen(ST(1))
;
	SV *	RETVAL;
    RETVAL = NULL;

    ERROR_XS_BEGIN()
    {
        RETVAL = newSV(decodeToBinSize(encodeType, source));
        SvPOK_only(RETVAL);

        decodeToBin(encodeType, source, (unsigned char *)SvPV_nolen(RETVAL));
        SvCUR_set(RETVAL, decodeToBinSize(encodeType, source));
    }
    ERROR_XS_END();
	RETVAL = sv_2mortal(RETVAL);
	ST(0) = RETVAL;
    }
    XSRETURN(1);
}


/* INCLUDE: Returning to 'LibC.xs' from 'xs/common/encode.xs' */

#ifdef __cplusplus
extern "C"
#endif
XS_EXTERNAL(boot_pgBackRest__LibC); /* prototype to pass -Wmissing-prototypes */
XS_EXTERNAL(boot_pgBackRest__LibC)
{
#if PERL_VERSION_LE(5, 21, 5)
    dVAR; dXSARGS;
#else
    dVAR; dXSBOOTARGSXSAPIVERCHK;
#endif
#if (PERL_REVISION == 5 && PERL_VERSION < 9)
    char* file = __FILE__;
#else
    const char* file = __FILE__;
#endif

    PERL_UNUSED_VAR(file);

    PERL_UNUSED_VAR(cv); /* -W */
    PERL_UNUSED_VAR(items); /* -W */
#if PERL_VERSION_LE(5, 21, 5)
    XS_VERSION_BOOTCHECK;
#  ifdef XS_APIVERSION_BOOTCHECK
    XS_APIVERSION_BOOTCHECK;
#  endif
#endif

        newXS_deffile("pgBackRest::LibC::libcUvSize", XS_pgBackRest__LibC_libcUvSize);
        newXS_deffile("pgBackRest::LibC::storageDriverPosixPathRemove", XS_pgBackRest__LibC_storageDriverPosixPathRemove);
        newXS_deffile("pgBackRest::LibC::pageChecksum", XS_pgBackRest__LibC_pageChecksum);
        newXS_deffile("pgBackRest::LibC::pageChecksumTest", XS_pgBackRest__LibC_pageChecksumTest);
        newXS_deffile("pgBackRest::LibC::pageChecksumBufferTest", XS_pgBackRest__LibC_pageChecksumBufferTest);
        newXS_deffile("pgBackRest::LibC::cryptoRandomBytes", XS_pgBackRest__LibC_cryptoRandomBytes);
        newXS_deffile("pgBackRest::LibC::Crypto::Hash::new", XS_pgBackRest__LibC__Crypto__Hash_new);
        newXS_deffile("pgBackRest::LibC::Crypto::Hash::process", XS_pgBackRest__LibC__Crypto__Hash_process);
        newXS_deffile("pgBackRest::LibC::Crypto::Hash::result", XS_pgBackRest__LibC__Crypto__Hash_result);
        newXS_deffile("pgBackRest::LibC::Crypto::Hash::DESTROY", XS_pgBackRest__LibC__Crypto__Hash_DESTROY);
        newXS_deffile("pgBackRest::LibC::cryptoHashOne", XS_pgBackRest__LibC_cryptoHashOne);
        newXS_deffile("pgBackRest::LibC::Cipher::Block::new", XS_pgBackRest__LibC__Cipher__Block_new);
        newXS_deffile("pgBackRest::LibC::Cipher::Block::process", XS_pgBackRest__LibC__Cipher__Block_process);
        newXS_deffile("pgBackRest::LibC::Cipher::Block::flush", XS_pgBackRest__LibC__Cipher__Block_flush);
        newXS_deffile("pgBackRest::LibC::Cipher::Block::DESTROY", XS_pgBackRest__LibC__Cipher__Block_DESTROY);
        newXS_deffile("pgBackRest::LibC::cfgCommandId", XS_pgBackRest__LibC_cfgCommandId);
        newXS_deffile("pgBackRest::LibC::cfgOptionId", XS_pgBackRest__LibC_cfgOptionId);
        newXS_deffile("pgBackRest::LibC::cfgDefOptionDefault", XS_pgBackRest__LibC_cfgDefOptionDefault);
        newXS_deffile("pgBackRest::LibC::cfgDefOptionPrefix", XS_pgBackRest__LibC_cfgDefOptionPrefix);
        newXS_deffile("pgBackRest::LibC::cfgDefOptionSecure", XS_pgBackRest__LibC_cfgDefOptionSecure);
        newXS_deffile("pgBackRest::LibC::cfgDefOptionType", XS_pgBackRest__LibC_cfgDefOptionType);
        newXS_deffile("pgBackRest::LibC::cfgDefOptionValid", XS_pgBackRest__LibC_cfgDefOptionValid);
        newXS_deffile("pgBackRest::LibC::cfgOptionTotal", XS_pgBackRest__LibC_cfgOptionTotal);
        newXS_deffile("pgBackRest::LibC::cfgParseTest", XS_pgBackRest__LibC_cfgParseTest);
        newXS_deffile("pgBackRest::LibC::cfgCommandName", XS_pgBackRest__LibC_cfgCommandName);
        newXS_deffile("pgBackRest::LibC::cfgOptionIndex", XS_pgBackRest__LibC_cfgOptionIndex);
        newXS_deffile("pgBackRest::LibC::cfgOptionIndexTotal", XS_pgBackRest__LibC_cfgOptionIndexTotal);
        newXS_deffile("pgBackRest::LibC::cfgOptionName", XS_pgBackRest__LibC_cfgOptionName);
        newXS_deffile("pgBackRest::LibC::lockAcquire", XS_pgBackRest__LibC_lockAcquire);
        newXS_deffile("pgBackRest::LibC::lockRelease", XS_pgBackRest__LibC_lockRelease);
        newXS_deffile("pgBackRest::LibC::encodeToStr", XS_pgBackRest__LibC_encodeToStr);
        newXS_deffile("pgBackRest::LibC::decodeToBin", XS_pgBackRest__LibC_decodeToBin);
#if PERL_VERSION_LE(5, 21, 5)
#  if PERL_VERSION_GE(5, 9, 0)
    if (PL_unitcheckav)
        call_list(PL_scopestack_ix, PL_unitcheckav);
#  endif
    XSRETURN_YES;
#else
    Perl_xs_boot_epilog(aTHX_ ax);
#endif
}
