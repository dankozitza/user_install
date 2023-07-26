cd ~;
mkdir .vimrc;
mkdir .vimrc/bundle;
mkdir .vimrc/plugins;
cd .vimrc/bundle; git clone https://github.com/justmao945/vim-clang;
cp vim-clang/plugins/clang.vim ~/.vimrc/plugins;
