// Scintilla source code edit control
// Document.h - text document that handles notifications, DBCS, styling, words and end of line
// Copyright 1998-2000 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.

#ifndef DOCUMENT_H
#define DOCUMENT_H

// A Position is a position within a document between two characters or at the beginning or end.
// Sometimes used as a character index where it identifies the character after the position.
typedef int Position;
const Position invalidPosition = -1;

// The range class represents a range of text in a document.
// The two values are not sorted as one end may be more significant than the other
// as is the case for the selection where the end position is the position of the caret.
// If either position is invalidPosition then the range is invalid and most operations will fail.
class Range {
public:
	Position start;
	Position end;
	
	Range(Position pos=0) : 
		start(pos), end(pos) {
	};
	Range(Position start_, Position end_) : 
		start(start_), end(end_) {
	};
	
	bool Valid() const {
		return (start != invalidPosition) && (end != invalidPosition);
	}
	
	bool Contains(Position pos) const {
		if (start < end) {
			return (pos >= start && pos <= end);
		} else {
			return (pos <= start && pos >= end);
		}
	}
	
	bool Contains(Range other) const {
		return Contains(other.start) && Contains(other.end);
	}
	
	bool Overlaps(Range other) const {
		return 
		Contains(other.start) ||
		Contains(other.end) ||
		other.Contains(start) ||
		other.Contains(end);
	}
};

class DocWatcher;
class DocModification;

class Document {

	// Used internally by Document
	class WatcherWithUserData {
	public:
		DocWatcher *watcher;
		void *userData;
		WatcherWithUserData() {
			watcher = 0;
			userData = 0;
		}
	};
	
	int refCount;
	CellBuffer cb;
	bool wordchars[256];
	bool modified;
	int stylingPos;
	int stylingMask;
	int endStyled;
	int enteredCount;
	
	WatcherWithUserData *watchers;
	int lenWatchers;
	
public:
	int eolMode;
	int dbcsCodePage;
	int tabInChars;
	
	Document();
	virtual ~Document();
	
	int AddRef();
	int Release();
 	
	int LineFromPosition(int pos);
	int ClampPositionIntoDocument(int pos);
	bool IsCrLf(int pos);
	int MovePositionOutsideChar(int pos, int moveDir, bool checkLineEnd=true);

	// Gateways to modifying document
	void DeleteChars(int pos, int len);
	void InsertStyledString(int position, char *s, int insertLength);
	int Undo();
	int Redo();
	bool CanUndo() { return cb.CanUndo(); }
	bool CanRedo() { return cb.CanRedo(); }
	void DeleteUndoHistory() { cb.DeleteUndoHistory(); }
	undoCollectionType SetUndoCollection(undoCollectionType collectUndo) {
		return cb.SetUndoCollection(collectUndo);
	}
	void AppendUndoStartAction() { cb.AppendUndoStartAction(); }
	void BeginUndoAction() { cb.BeginUndoAction(); }
	void EndUndoAction() { cb.EndUndoAction(); }
	void SetSavePoint() { cb.SetSavePoint(); }
	bool IsSavePoint() { return cb.IsSavePoint(); }
	void Indent(bool forwards, int lineBottom, int lineTop);
	void ConvertLineEnds(int eolModeSet);
	void SetReadOnly(bool set) { cb.SetReadOnly(set); }

	void InsertChar(int pos, char ch);
	void InsertString(int position, const char *s);
	void InsertString(int position, const char *s, int insertLength);
	void DelChar(int pos);
	int DelCharBack(int pos);

	char CharAt(int position) { return cb.CharAt(position); }
	void GetCharRange(char *buffer, int position, int lengthRetrieve) {
		cb.GetCharRange(buffer, position, lengthRetrieve);
	}
	char StyleAt(int position) { return cb.StyleAt(position); }
	int GetMark(int line) { return cb.GetMark(line); }
	int AddMark(int line, int markerNum) { return cb.AddMark(line, markerNum); }
	void DeleteMark(int line, int markerNum) { cb.DeleteMark(line, markerNum); }
	void DeleteMarkFromHandle(int markerHandle) { cb.DeleteMarkFromHandle(markerHandle); }
	void DeleteAllMarks(int markerNum) { cb.DeleteAllMarks(markerNum); }
	int LineFromHandle(int markerHandle) { return cb.LineFromHandle(markerHandle); }
	int LineStart(int line);
	int LineEndPosition(int position);
	int VCHomePosition(int position);

	void Indent(bool forwards);
	int ExtendWordSelect(int pos, int delta);
	int NextWordStart(int pos, int delta);
	int Length() { return cb.Length(); }
	long FindText(int minPos, int maxPos, const char *s, bool caseSensitive, bool word);
	long FindText(WORD iMessage,WPARAM wParam,LPARAM lParam);
	int LinesTotal();
	
	void SetWordChars(unsigned char *chars);
	void StartStyling(int position, char mask);
	void SetStyleFor(int length, char style);
	void SetStyles(int length, char *styles);
	int GetEndStyled() { return endStyled; }
	
	bool AddWatcher(DocWatcher *watcher, void *userData);
	bool RemoveWatcher(DocWatcher *watcher, void *userData);
	
private:
	bool IsDBCS(int pos);
	bool IsWordChar(unsigned char ch);
	bool IsWordAt(int start, int end);
	void ModifiedAt(int pos);
		
	void NotifyModifyAttempt();
	void NotifySavePoint(bool atSavePoint);
	void NotifyModified(DocModification mh);
};

// To optimise processing of document modifications by DocWatchers, a hint is passed indicating the 
// scope of the change.
// If the DocWatcher is a document view then this can be used to optimise screen updating.
class DocModification {
public:
  	int modificationType;
	int position;
 	int length;
 	int linesAdded;	// Negative if lines deleted
 	const char *text;	// Only valid for changes to text, not for changes to style

	DocModification(int modificationType_, int position_=0, int length_=0, 
		int linesAdded_=0, const char *text_=0) :
		modificationType(modificationType_),
		position(position_),
		length(length_),
		linesAdded(linesAdded_),
		text(text_) {}
};

// A class that wants to receive notifications from a Document must be derived from DocWatcher 
// and implement the notification methods. It can then be added to the watcher list with AddWatcher.
class DocWatcher {
public:
	virtual void NotifyModifyAttempt(Document *doc, void *userData) = 0;
	virtual void NotifySavePoint(Document *doc, void *userData, bool atSavePoint) = 0;
	virtual void NotifyModified(Document *doc, DocModification mh, void *userData) = 0;
};

#endif
