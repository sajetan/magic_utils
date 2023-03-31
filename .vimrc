
" lines of history
set history=500

" Enable filetype plugins
filetype plugin on
filetype indent on

" Set to auto read when a file is changed from the outside
set autoread
au FocusGained,BufEnter * checktime

" With a map leader it's possible to do extra key combinations
" like <leader>w saves the current file
let mapleader = ","


" :W sudo saves the file
" (useful for handling the permission-denied error)
command! W execute 'w !sudo tee % > /dev/null' <bar> edit!


"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" current position
set ruler

" Height of the command bar
set cmdheight=1

" A buffer becomes hidden when it is abandoned
set hid

" Configure backspace so it acts as it should act
set backspace=eol,start,indent
set whichwrap+=<,>,h,l

" ignore case when searching
set ignorecase
set smartcase

" highlight search
set hlsearch

" Makes search act like search in modern browsers
set incsearch

" matching brackets
set showmatch

" blink sec matching brackets
set mat=2


" Add a bit extra margin to the left
set foldcolumn=0

nmap <F8> :TagbarToggle<CR>

" colors
" syntax highlighting
syntax enable


" enable 256 colors palette in Gnome Terminal
if $COLORTERM == 'gnome-terminal'
    set t_Co=256
endif

try
    colorscheme desert
catch
endtry

set background=dark


" Set utf8 as standard encoding and en_US as the standard language
set encoding=utf8

" file related stuff
set undofile
set nobackup
set nowb
set noswapfile


" spaces instead of tabs
set expandtab
set smarttab

" 1 tab == 4 spaces
set shiftwidth=4
set tabstop=4

" linebreak on 500 characters
set lbr
set tw=500

" indent fixes
set autoindent 
set smartindent 
set wrap 

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" plugins
call plug#begin('~/.vim/plugged')
  Plug 'dense-analysis/ale'
  Plug 'preservim/nerdtree'
  Plug 'majutsushi/tagbar'
call plug#end()

"""tmux related
"set mouse=a
