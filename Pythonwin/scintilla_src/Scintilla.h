// Scintilla source code edit control
// Scintilla.h - interface to the edit control
// Copyright 1998-2000 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.

#ifndef SCINTILLA_H
#define SCINTILLA_H

#ifdef PLAT_GTK
#include <gdk/gdk.h>
#include <gtk/gtkvbox.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCINTILLA(obj)          GTK_CHECK_CAST (obj, scintilla_get_type (), ScintillaObject)
#define SCINTILLA_CLASS(klass)  GTK_CHECK_CLASS_CAS	T (klass, scintilla_get_type (), ScintillaClass)
#define IS_SCINTILLA(obj)       GTK_CHECK_TYPE (obj, scintilla_get_type ())

	typedef struct _ScintillaObject ScintillaObject;
	typedef struct _ScintillaClass  ScintillaClass;

	struct _ScintillaObject
	{
		GtkFixed vbox;
		void *pscin;
	};

	struct _ScintillaClass
	{
		GtkFixedClass parent_class;

		void (* command) (ScintillaObject *ttt);
		void (* notify) (ScintillaObject *ttt);
	};

	guint		scintilla_get_type	(void);
	GtkWidget*	scintilla_new		(void);
	void		scintilla_set_id	(ScintillaObject *sci,int id);
	long 		scintilla_send_message	(ScintillaObject *sci,int iMessage,int wParam,int lParam);

#include "WinDefs.h"

#ifdef __cplusplus
}
#endif

#endif

// Both GTK and Windows

#define INVALID_POSITION -1 

// Define start of Scintilla messages to be greater than all edit (EM_*) messages
// as many EM_ messages can be used.
#define SCI_START 2000

#define SCI_ADDTEXT SCI_START + 1
#define SCI_ADDSTYLEDTEXT SCI_START + 2
#define SCI_INSERTTEXT SCI_START + 3
#define SCI_CLEARALL SCI_START + 4
#define SCI_GETLENGTH SCI_START + 6
#define SCI_GETCHARAT SCI_START + 7
#define SCI_GETCURRENTPOS SCI_START + 8
#define SCI_GETANCHOR SCI_START + 9
#define SCI_GETSTYLEAT SCI_START + 10

#define SCI_REDO SCI_START + 11
#define SCI_SETUNDOCOLLECTION SCI_START + 12
#define SCI_SELECTALL SCI_START + 13
#define SCI_SETSAVEPOINT SCI_START + 14
#define SCI_GETSTYLEDTEXT SCI_START + 15
#define SCI_CANREDO SCI_START + 16
#define SCI_MARKERLINEFROMHANDLE SCI_START + 17
#define SCI_MARKERDELETEHANDLE SCI_START + 18

#define SC_UNDOCOLLECT_NONE 0
#define SC_UNDOCOLLECT_AUTOSTART 1

#define SCI_GETVIEWWS SCI_START + 20
#define SCI_SETVIEWWS SCI_START + 21
#define SCI_CHANGEPOSITION SCI_START + 22
#define SCI_GOTOLINE SCI_START + 24
#define SCI_GOTOPOS SCI_START + 25
#define SCI_SETANCHOR SCI_START + 26
#define SCI_GETCURLINE SCI_START + 27
#define SCI_GETENDSTYLED SCI_START + 28
#define SCI_CONVERTEOLS SCI_START + 29

#define SCI_GETEOLMODE SCI_START + 30
#define SCI_SETEOLMODE SCI_START + 31

#define SC_EOL_CRLF 0
#define SC_EOL_CR 1
#define SC_EOL_LF 2

#define SCI_STARTSTYLING SCI_START + 32
#define SCI_SETSTYLING SCI_START + 33

#define SCI_SETMARGINWIDTH SCI_START + 34
#define SCI_SETBUFFEREDDRAW SCI_START + 35
#define SCI_SETTABWIDTH SCI_START + 36
#define SCI_SETCODEPAGE SCI_START + 37
#define SCI_SETLINENUMBERWIDTH SCI_START + 38
#define SCI_SETUSEPALETTE SCI_START + 39

#define MARKER_MAX 31

#define SC_MARK_CIRCLE 0
#define SC_MARK_ROUNDRECT 1
#define SC_MARK_ARROW 2
#define SC_MARK_SMALLRECT 3
#define SC_MARK_SHORTARROW 4
#define SC_MARK_EMPTY 5

#define SCI_MARKERDEFINE SCI_START + 40
#define SCI_MARKERSETFORE SCI_START + 41
#define SCI_MARKERSETBACK SCI_START + 42
#define SCI_MARKERADD SCI_START + 43
#define SCI_MARKERDELETE SCI_START + 44
#define SCI_MARKERDELETEALL SCI_START + 45
#define SCI_MARKERGET SCI_START + 46
#define SCI_MARKERNEXT SCI_START + 47
#define SCI_MARKERPREVIOUS SCI_START + 48

#define LEX_STYLE_MAX 31
#define STYLE_DEFAULT 32
#define STYLE_LINENUMBER 33
#define STYLE_BRACELIGHT 34
#define STYLE_BRACEBAD 35
#define STYLE_CONTROLCHAR 36
#define STYLE_MAX 36

#define SCI_STYLECLEARALL SCI_START + 50
#define SCI_STYLESETFORE SCI_START + 51
#define SCI_STYLESETBACK SCI_START + 52
#define SCI_STYLESETBOLD SCI_START + 53
#define SCI_STYLESETITALIC SCI_START + 54
#define SCI_STYLESETSIZE SCI_START + 55
#define SCI_STYLESETFONT SCI_START + 56
#define SCI_STYLESETEOLFILLED SCI_START + 57
#define SCI_STYLERESETDEFAULT SCI_START + 58

#define SCI_SETSELFORE SCI_START + 67
#define SCI_SETSELBACK SCI_START + 68
#define SCI_SETCARETFORE SCI_START + 69

#define SCI_ASSIGNCMDKEY SCI_START + 70
#define SCI_CLEARCMDKEY SCI_START + 71
#define SCI_CLEARALLCMDKEYS SCI_START + 72

#define SCI_SETSTYLINGEX SCI_START + 73

#define SCI_GETCARETPERIOD SCI_START + 75
#define SCI_SETCARETPERIOD SCI_START + 76
#define SCI_SETWORDCHARS SCI_START + 77

#define SCI_BEGINUNDOACTION SCI_START + 78
#define SCI_ENDUNDOACTION SCI_START + 79

#define INDIC_MAX 2

#define INDIC_PLAIN 0
#define INDIC_SQUIGGLE 1
#define INDIC_TT 2

#define INDIC0_MASK 32
#define INDIC1_MASK 64
#define INDIC2_MASK 128
#define INDICS_MASK (INDIC0_MASK | INDIC1_MASK | INDIC2_MASK)

#define SCI_INDICSETSTYLE SCI_START + 80
#define SCI_INDICGETSTYLE SCI_START + 81
#define SCI_INDICSETFORE SCI_START + 82
#define SCI_INDICGETFORE SCI_START + 83

#define SCI_AUTOCSHOW SCI_START + 100
#define SCI_AUTOCCANCEL SCI_START + 101
#define SCI_AUTOCACTIVE SCI_START + 102
#define SCI_AUTOCPOSSTART SCI_START + 103
#define SCI_AUTOCCOMPLETE SCI_START + 104
#define SCI_AUTOCSTOPS SCI_START + 105

#define SCI_CALLTIPSHOW SCI_START + 200
#define SCI_CALLTIPCANCEL SCI_START + 201
#define SCI_CALLTIPACTIVE SCI_START + 202
#define SCI_CALLTIPPOSSTART SCI_START + 203
#define SCI_CALLTIPSETHLT SCI_START + 204
#define SCI_CALLTIPSETBACK SCI_START + 205

// Key messages
#define SCI_LINEDOWN SCI_START + 300
#define SCI_LINEDOWNEXTEND SCI_START + 301
#define SCI_LINEUP SCI_START + 302
#define SCI_LINEUPEXTEND SCI_START + 303
#define SCI_CHARLEFT SCI_START + 304
#define SCI_CHARLEFTEXTEND SCI_START + 305
#define SCI_CHARRIGHT SCI_START + 306
#define SCI_CHARRIGHTEXTEND SCI_START + 307
#define SCI_WORDLEFT SCI_START + 308
#define SCI_WORDLEFTEXTEND SCI_START + 309
#define SCI_WORDRIGHT SCI_START + 310
#define SCI_WORDRIGHTEXTEND SCI_START + 311
#define SCI_HOME SCI_START + 312
#define SCI_HOMEEXTEND SCI_START + 313
#define SCI_LINEEND SCI_START + 314
#define SCI_LINEENDEXTEND SCI_START + 315
#define SCI_DOCUMENTSTART SCI_START + 316
#define SCI_DOCUMENTSTARTEXTEND SCI_START + 317
#define SCI_DOCUMENTEND SCI_START + 318
#define SCI_DOCUMENTENDEXTEND SCI_START + 319
#define SCI_PAGEUP SCI_START + 320
#define SCI_PAGEUPEXTEND SCI_START + 321
#define SCI_PAGEDOWN SCI_START + 322
#define SCI_PAGEDOWNEXTEND SCI_START + 323
#define SCI_EDITTOGGLEOVERTYPE SCI_START + 324
#define SCI_CANCEL SCI_START + 325
#define SCI_DELETEBACK SCI_START + 326
#define SCI_TAB SCI_START + 327
#define SCI_BACKTAB SCI_START + 328
#define SCI_NEWLINE SCI_START + 329
#define SCI_FORMFEED SCI_START + 330
#define SCI_VCHOME SCI_START + 331
#define SCI_VCHOMEEXTEND SCI_START + 332
#define SCI_ZOOMIN SCI_START + 333
#define SCI_ZOOMOUT SCI_START + 334
#define SCI_DELWORDLEFT SCI_START + 335
#define SCI_DELWORDRIGHT SCI_START + 336

#define SCI_LINELENGTH SCI_START + 350
#define SCI_BRACEHIGHLIGHT SCI_START + 351
#define SCI_BRACEBADLIGHT SCI_START + 352
#define SCI_BRACEMATCH SCI_START + 353
#define SCI_GETVIEWEOL SCI_START + 355
#define SCI_SETVIEWEOL SCI_START + 356
#define SCI_GETDOCPOINTER SCI_START + 357
#define SCI_SETDOCPOINTER SCI_START + 358
#define SCI_SETMODEVENTMASK SCI_START + 359

#define EDGE_NONE 0
#define EDGE_LINE 1
#define EDGE_BACKGROUND 2

#define SCI_GETEDGECOLUMN SCI_START + 360
#define SCI_SETEDGECOLUMN SCI_START + 361
#define SCI_GETEDGEMODE SCI_START + 362
#define SCI_SETEDGEMODE SCI_START + 363
#define SCI_GETEDGECOLOUR SCI_START + 364
#define SCI_SETEDGECOLOUR SCI_START + 365

// GTK+ Specific
#define SCI_GRABFOCUS SCI_START + 400

// Notifications

// Type of modification and the action which caused the modification
// These are defined as a it mask to make it easy to specify which notifications are wanted.
// One bit is set from each of SC_MOD_* and SC_PERFORMED_*.
#define SC_MOD_INSERTTEXT 0x1
#define SC_MOD_DELETETEXT 0x2
#define SC_MOD_CHANGESTYLE 0x4
#define SC_PERFORMED_USER 0x10
#define SC_PERFORMED_UNDO 0x20
#define SC_PERFORMED_REDO 0x40
#define SC_LASTSTEPINUNDOREDO 0x100

#define SC_MODEVENTMASKALL 0x377

struct SCNotification {
	NMHDR nmhdr;
	int position;			// SCN_STYLENEEDED, SCN_MODIFIED
	int ch;					// SCN_CHARADDED, SCN_KEY
	int modifiers;			// SCN_KEY
  	int modificationType;	// SCN_MODIFIED
 	const char *text;		// SCN_MODIFIED
 	int length;				// SCN_MODIFIED
 	int linesAdded;	// SCN_MODIFIED
};

#define SCN_STYLENEEDED 2000
#define SCN_CHARADDED 2001
#define SCN_SAVEPOINTREACHED 2002
#define SCN_SAVEPOINTLEFT 2003
#define SCN_MODIFYATTEMPTRO 2004
// GTK+ Specific to work around focus and accelerator problems:
#define SCN_KEY 2005
#define SCN_DOUBLECLICK 2006
#define SCN_UPDATEUI 2007
// The old name for SCN_UPDATEUI:
#define SCN_CHECKBRACE 2007
#define SCN_MODIFIED 2008

#ifdef STATIC_BUILD
void Scintilla_RegisterClasses(HINSTANCE hInstance);
#endif

// Deprecation section listing all API features that are deprecated and will
// will be removed completely in a future version.
// To enable these features define INCLUDE_DEPRECATED_FEATURES

#ifdef INCLUDE_DEPRECATED_FEATURES

// Default style settings. These are deprecated and will be removed in a future version.
#define SCI_SETFORE SCI_START + 60
#define SCI_SETBACK SCI_START + 61
#define SCI_SETBOLD SCI_START + 62
#define SCI_SETITALIC SCI_START + 63
#define SCI_SETSIZE SCI_START + 64
#define SCI_SETFONT SCI_START + 65

#define SCI_APPENDUNDOSTARTACTION SCI_START + 74

#define SC_UNDOCOLLECT_MANUALSTART 2

#endif

#endif
