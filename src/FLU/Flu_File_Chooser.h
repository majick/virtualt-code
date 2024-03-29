// $Id$

/***************************************************************
 *                FLU - FLTK Utility Widgets 
 *  Copyright (C) 2002 Ohio Supercomputer Center, Ohio State University
 *
 * This file and its content is protected by a software license.
 * You should have received a copy of this license with this file.
 * If not, please contact the Ohio Supercomputer Center immediately:
 * Attn: Jason Bryan Re: FLU 1224 Kinnear Rd, Columbus, Ohio 43212
 * 
 ***************************************************************/



#ifndef _FLU_FILE_CHOOSER_H
#define _FLU_FILE_CHOOSER_H

#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Check_Button.H>

#include "FLU/Flu_Button.h"
#include "FLU/Flu_Return_Button.h"
#include "FLU/Flu_Wrap_Group.h"
#include "FLU/Flu_Combo_Tree.h"
#include "FLU/Flu_Combo_List.h"
#include "FLU/flu_export.h"
#include "FLU/FluSimpleString.h"
#include "FLU/VectorClass.h"

FLU_EXPORT const char* flu_file_chooser( const char *message, const char *pattern, const char *filename );
FLU_EXPORT const char* flu_dir_chooser( const char *message, const char *filename );

MakeVectorClass( FluSimpleString, StringVector );

//! A file and directory choosing widget that looks and acts similar to the stock Windows file chooser
class FLU_EXPORT Flu_File_Chooser : public Fl_Double_Window
{

  friend class FileInput;
  class FileInput : public Fl_Input
    {
    public:
      FileInput( int x, int y, int w, int h, const char *l, Flu_File_Chooser *c );
      ~FileInput();

      int handle( int event );
    protected:
      Flu_File_Chooser *chooser;
    };

 public:

  //! This class must be derived from to create a "preview" widget.
  /*! Simply derive from this class and overload Fl_Group's methods to create a widget
    able to preview whatever file type you want. Register it with Flu_File_Chooser::add_preview_handler()
    When a file is previewed, all registered handlers are visited until the preview() virtual function
    for one of them returns nonzero. When preview() is called, the absolute path of the file is passed in,
    and the widget should determine whether it can preview the file and update itself accordingly. If
    it can preview the file, it should return nonzero, else it should return zero.
   */
  class PreviewWidgetBase : public Fl_Group
    {
    public:
      PreviewWidgetBase();
      virtual ~PreviewWidgetBase();
      virtual int preview( const char *filename ) = 0;
    };

  //! File entry type
  enum { 
    ENTRY_NONE = 1,         /*!< An empty (or non-existant) entry */
    ENTRY_DIR = 2,          /*!< A directory entry */
    ENTRY_FILE = 4,         /*!< A file entry */
    ENTRY_FAVORITE = 8,     /*!< A favorite entry */
    ENTRY_DRIVE = 16,       /*!< An entry that refers to a disk drive */
    ENTRY_MYDOCUMENTS = 32, /*!< The entry referring to the current user's documents */
    ENTRY_MYCOMPUTER = 64   /*!< The entry referring to "My Computer" in Windows */
  };

  //! Chooser type
  enum { 
    SINGLE = 0,    /*!< Chooser a single file or directory */
    MULTI = 1,     /*!< Choose multiple files or directories */
    DIRECTORY = 4  /*!< Choose directories (choosing files is implicit if this bit is clear) */
  };

  //! Structure holding the info needed for custom file types
  struct FileTypeInfo
  {
    Fl_Image *icon;
    FluSimpleString extensions;
    FluSimpleString type, shortType;
  };

  //! Constructor opening a file chooser with title \b title visiting directory \b path with files filtered according to \b pattern. \b type is a logical OR of Flu_File_Chooser::SINGLE, Flu_File_Chooser::MULTI, and Flu_File_Chooser::DIRECTORY 
  Flu_File_Chooser( const char *path, const char *pattern, int type, const char *title );

  //! Destructor
  ~Flu_File_Chooser();

  //! Add a custom callback that is called when the user right-clicks on an entry
  /*! \param type is the type of entry to handle (i.e. a logical OR of \c ENTRY_NONE, \c ENTRY_DIR, \c ENTRY_FILE, \c ENTRY_FAVORITE, \c ENTRY_DRIVE, \c ENTRY_MYDOCUMENTS, \c ENTRY_MYCOMPUTER). To add a "nothing" handler (when the user right-clicks on nothing), use ENTRY_NONE
    \param ext is the extension of the file that will cause this handler to be added to the popup menu
    \param name is the name that will appear in the popup menu for this handler
   */
  static void add_context_handler( int type, const char *ext, const char *name,
				   void (*cb)(const char*,int,void*), void *cbd );

  //! Add a "preview" widget (derived from class Flu_File_Chooser::PreviewWidgetBase) that will handle custom previewing of files
  static void add_preview_handler( PreviewWidgetBase *w );

  //! Add descriptive information and an icon for a file type
  /*! \param extensions is a space- or comma-delimited list of file extensions, or \c NULL for directories. e.g. "zip,tgz,rar"
    \param short_description is a short description (!) of the file type. e.g. "Compressed Archive"
    \param icon is an optional custom icon to use for this file type
   */
  static void add_type( const char *extensions, const char *short_description, Fl_Image *icon = NULL );

  //! Set whether the names of files/directories are allowed to be edited by the user (by selecting the file and then clicking on it again). Default is on (true)
  inline void allow_file_editing( int b )
    { fileEditing = b; }

  //! Get whether the names of files/directories are allowed to be edited by the user (by selecting the file and then clicking on it again)
  inline int allow_file_editing() const
    { return fileEditing; }

  //! Set whether file sorting is case insensitive. Default value is case-insensitive for windows, case-sensitive for everything else
  inline void case_insensitive_sort( int b )
    { caseSort = !b; }

  //! Get whether file sorting is case insensitive
  inline int case_insensitive_sort() const
    { return !caseSort; }

  //! Change the current directory the chooser is browsing to \b path
  void cd( const char *path );

  //! Clear the history of which directories have been visited
  void clear_history();

  //! \return how many files are selected
  int count();

  //! Set the default icon to use for all files for which no other icon has been specified
  inline void default_file_icon( Fl_Image* i )
    { defaultFileIcon = i; }

  //! Alias for cd()
  inline void directory( const char *d )
    { cd( d ); }

  //! Alias for pattern()
  inline void filter( const char *p )
    { pattern( p ); }

  //! Alias for pattern()
  inline const char* filter() const
    { return pattern(); }

  //! \return a pointer to a FileTypeInfo structure for files with type \b extension
  static FileTypeInfo *find_type( const char *extension );

  //! \return the current directory that the browser is visiting
  inline const char* get_current_directory() const
    { return currentDir.c_str(); }

  //! Override of Fl_Double_Window::handle()
  int handle( int event );

  //! Change the file filter pattern to \b p
  void pattern( const char *p );

  //! Get the current file filter pattern
  inline const char* pattern() const
    { return rawPattern.c_str(); }

  //! Set the state of the preview button
  inline void preview( int b )
    { previewBtn->value(b); previewBtn->do_callback(); }

  //! Get the state of the preview button
  inline int preview() const
    { return previewBtn->value(); }

  //! Refresh the current directory
  inline void rescan() { reloadCB(); }

  //! Override of Fl_Double_Window::resize()
  void resize( int x, int y, int w, int h );

  //! Set a custom sorting function for sorting entries based on filename
  inline void set_sort_function( int (*cb)(const char*,const char*) )
    { customSort = cb; rescan(); }

  //! Unselect all entries
  void unselect_all();

  //! Set the current file the chooser is selecting
  void value( const char *v );

  //! Get the current file the chooser is selecting
  const char *value();

  //! For MULTI file queries, get selected file \b n
  const char *value( int n );

  FileInput filename;
  // the <Enter> key behavior is not correct for versions before 1.1.4rc2
#if FL_MAJOR_VERSION >= 1 && FL_MINOR_VERSION >= 1 && FL_PATCH_VERSION >= 4
  Flu_Return_Button ok;
#else
  Flu_Button ok;
#endif
  Flu_Button cancel;

  // apparently there is a bug in VC6 that prevents friend classes from accessing
  // non-public members. stupid windows
  // several other compilers were reported to have a problem with this too, so 
  // i'm just making the whole class public to eliminate potential problems.
  // bad c++ - i know...
  //#ifndef WIN32
  //protected:
  //#endif

  class ContextHandler
    {
    public:
      FluSimpleString ext, name;
      int type;
      void (*callback)(const char*,int,void*);
      void *callbackData;
      inline ContextHandler& operator =( const ContextHandler &c )
      { ext = c.ext; name = c.name; type = c.type; callback = c.callback; callbackData = c.callbackData; return *this; }
    };
  MakeVectorClass( ContextHandler, ContextHandlerVector );
  static ContextHandlerVector contextHandlers;

  typedef PreviewWidgetBase* pPreviewWidgetBase;
  MakeVectorClass( pPreviewWidgetBase, PreviewHandlerVector );
  static PreviewHandlerVector previewHandlers;

  Fl_Check_Button *hiddenFiles;
  Flu_Combo_Tree *filesystems;

  inline static void _backCB( Fl_Widget *w, void *arg )
    { ((Flu_File_Chooser*)arg)->backCB(); }
  void backCB();

  inline static void _forwardCB( Fl_Widget *w, void *arg )
    { ((Flu_File_Chooser*)arg)->forwardCB(); }
  void forwardCB();

  inline static void _sortCB( Fl_Widget *w, void *arg )
    { ((Flu_File_Chooser*)arg)->sortCB( w ); }
  void sortCB( Fl_Widget *w );

  inline static void _previewCB( Fl_Widget*, void *arg )
    { ((Flu_File_Chooser*)arg)->previewCB(); }
  void previewCB();

  inline static void _filenameCB( Fl_Widget *w, void *arg )
    { ((Flu_File_Chooser*)arg)->filenameCB(); }
  void filenameCB();

  inline static void _filesystemsCB( Fl_Widget *w, void *arg )
    { ((Flu_File_Chooser*)arg)->filesystemsCB( ((Flu_Combo_Tree*)w)->value() ); }
  void filesystemsCB( const char *path );

  inline static void delayedCdCB( void *arg )
    { ((Flu_File_Chooser*)arg)->cd( ((Flu_File_Chooser*)arg)->delayedCd.c_str() ); }

  inline static void selectCB( void *arg )
    { ((Flu_File_Chooser*)arg)->hide(); }

  inline static void _cancelCB( Fl_Widget*, void *arg )
    { ((Flu_File_Chooser*)arg)->cancelCB(); }
  void cancelCB();

  inline static void _okCB( Fl_Widget*, void *arg )
    { ((Flu_File_Chooser*)arg)->okCB(); }
  void okCB();

  inline static void _trashCB( Fl_Widget*, void *arg )
    { ((Flu_File_Chooser*)arg)->trashCB(); }
  void trashCB( int recycle = true );

  inline static void _newFolderCB( Fl_Widget*, void *arg )
    { ((Flu_File_Chooser*)arg)->newFolderCB(); }
  void newFolderCB();

  inline static void upDirCB( Fl_Widget*, void *arg )
    { ((Flu_File_Chooser*)arg)->cd( "../" ); }

  inline static void reloadCB( Fl_Widget*, void *arg )
    { ((Flu_File_Chooser*)arg)->reloadCB(); }
  void reloadCB();

  inline static void _homeCB( Fl_Widget*, void *arg )
    { ((Flu_File_Chooser*)arg)->homeCB(); }
  void homeCB();

  inline static void _desktopCB( Fl_Widget*, void *arg )
    { ((Flu_File_Chooser*)arg)->desktopCB(); }
  void desktopCB();

  inline static void _favoritesCB( Fl_Widget*, void *arg )
    { ((Flu_File_Chooser*)arg)->favoritesCB(); }
  void favoritesCB();

  inline static void _myComputerCB( Fl_Widget*, void *arg )
    { ((Flu_File_Chooser*)arg)->myComputerCB(); }
  void myComputerCB();

  inline static void _addToFavoritesCB( Fl_Widget*, void *arg )
    { ((Flu_File_Chooser*)arg)->addToFavoritesCB(); }
  void addToFavoritesCB();

  inline static void _documentsCB( Fl_Widget*, void *arg )
    { ((Flu_File_Chooser*)arg)->documentsCB(); }
  void documentsCB();

  enum {
    SORT_NAME = 1,
    SORT_SIZE = 2,
    SORT_TYPE = 4,
    SORT_DATE = 8,
    SORT_REVERSE = 16 
  };
  static void _qSort( int how, int caseSort, Fl_Widget **array, int low, int high );

  friend class Entry;
  class Entry : public Fl_Input
    {
    public:
      Entry( const char* name, int t, int d, Flu_File_Chooser *c );
      ~Entry();

      int handle( int event );
      void draw();

      void updateSize();
      void updateIcon();

      FluSimpleString filename, date, filesize, shortname, 
	description, shortDescription, toolTip, altname;
      //FluSimpleString permissions;
      //unsigned char pU, pG, pO; // 3-bit unix style permissions
      unsigned int type, idate;
      unsigned long isize;
      int selected;
      int editMode;
      Flu_File_Chooser *chooser;
      Fl_Image *icon;

      int nameW, typeW, sizeW, dateW;
      int details;

      inline static void _inputCB( Fl_Widget *w, void *arg )
	{ ((Entry*)arg)->inputCB(); }
      void inputCB();

      inline static void _editCB( void *arg )
	{ ((Entry*)arg)->editCB(); }
      void editCB();
    };

  friend class FileList;
  class FileList : public Flu_Wrap_Group
    {
    public:
      FileList( int x, int y, int w, int h, Flu_File_Chooser *c );
      ~FileList();

      int handle( int event );
      void sort( int numDirs = -1 );

      int numDirs;
      Flu_File_Chooser *chooser;
    };

  friend class FileDetails;
  class FileDetails : public Fl_Pack
    {
    public:
      FileDetails( int x, int y, int w, int h, Flu_File_Chooser *c );
      ~FileDetails();

      int handle( int event );
      void sort( int numDirs = -1 );

      void scroll_to( Fl_Widget *w );

      int numDirs;
      Flu_File_Chooser *chooser;
    };

  friend class CBTile;
  class CBTile : public Fl_Tile
    {
    public:
      CBTile( int x, int y, int w, int h, Flu_File_Chooser *c );
      int handle( int event );
      Flu_File_Chooser *chooser;
    };

  friend class FileColumns;
  class FileColumns : public Fl_Tile
    {
    public:
      FileColumns( int x, int y, int w, int h, Flu_File_Chooser *c );
      ~FileColumns();

      int handle( int event );
      void resize( int x, int y, int w, int h );
      Flu_File_Chooser *chooser;
      int W1, W2, W3, W4;
    };

  friend class PreviewTile;
  class PreviewTile : public Fl_Tile
    {
    public:
      PreviewTile( int x, int y, int w, int h, Flu_File_Chooser *c );
      int handle( int event );
      Flu_File_Chooser *chooser;
      int last;
    };

  class ImgTxtPreview : public PreviewWidgetBase
    {
    public:
      int preview( const char *filename );
      unsigned char previewTxt[1024];
    };

  friend class PreviewGroup;
  class PreviewGroup : public Fl_Group
    {
    public:
      PreviewGroup( int x, int y, int w, int h, Flu_File_Chooser *c );
      void draw();
      Flu_File_Chooser *chooser;
      FluSimpleString lastFile, file;
      PreviewWidgetBase* handled;
    };

  Fl_Group *getEntryGroup();

  void win2unix( FluSimpleString &s );

  void cleanupPath( FluSimpleString &s );

  int correctPath( FluSimpleString &path );

  void updateEntrySizes();

  void buildFilesystemsCombo();

  void addToHistory();

  FluSimpleString formatDate( const char *d );

  void recursiveScan( const char *dir, StringVector *files );

  int stripPatterns( FluSimpleString s, StringVector* patterns );

  int popupContextMenu( Entry *entry );

  FluSimpleString commonStr();

  static ImgTxtPreview *imgTxtPreview;

  static int (*customSort)(const char*,const char*);

  PreviewGroup *previewGroup;
  PreviewTile *previewTile;
  Fl_Group *fileGroup;
  Fl_Menu_Button entryPopup;
  Fl_Image *defaultFileIcon;
  Entry *lastSelected;
  FileList *filelist;
  FileColumns *filecolumns;
  Fl_Scroll *filescroll;
  FileDetails *filedetails;
  Flu_Button *detailNameBtn, *detailTypeBtn, *detailSizeBtn, *detailDateBtn;
  FluSimpleString currentDir, delayedCd, rawPattern;
  FluSimpleString userHome, configFilename;
  FluSimpleString drives[26];
  Fl_Pixmap* driveIcons[26];
  Flu_Button *fileListBtn, *fileListWideBtn, *fileDetailsBtn, *backBtn, *forwardBtn, *upDirBtn, *trashBtn,
    *newDirBtn, *addFavoriteBtn, *reloadBtn, *previewBtn;
  Fl_Browser *favoritesList;
  Flu_Combo_List *filePattern;
  int selectionType;
  int filenameEnterCallback, filenameTabCallback, walkingHistory, caseSort, fileEditing;
  int sortMethod;

  StringVector patterns;

  static FileTypeInfo *types;
  static int numTypes;
  static int typeArraySize;

#ifdef WIN32
  unsigned int driveMask;
  unsigned int driveTypes[26];
  FluSimpleString volumeNames[26];
  int refreshDrives;
#endif

  class History
  {
  public:
    History() { last = next = NULL; }
    FluSimpleString path;
    History *last, *next;
  };

  History *history, *currentHist;

};

#endif
