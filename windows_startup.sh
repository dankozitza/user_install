# windows_startup.sh

pdir="$HOME/p"

if [ yes ]; then
	echo "Install Windows Subsystem for Linux and OracleLinux.";

	#echo "Script must be configured!";
	exit;
fi

if [ ! yes ]; then
echo "Installing applications"
#sudo dnf install screen
#sudo dnf install vim
#sudo dnf install clang
sudo dnf install gcc
sudo dnf install gcc-c++
#sudo dnf install make
#sudo dnf install jsoncpp

echo "Configuring applications"
#cp userhome/.bashrc ~
cp userhome/.vimrc ~

echo "Dont forget to call screen!"
fi

if [ ! yes ]; then
echo "Configuring git"
git config --system user.name "dankozitza"
git config --system user.email "dankoz@gmx.us"
git config --system color.diff always
git config --system color.status true
git config --system credential.helper store
fi

if [ ! yes ]; then
   echo "Downloading rndstream"
   mkdir $pdir
   git clone https://github.com/dankozitza/rndstream $pdir/rndstream
   echo "Building rndstream"
   make -C $pdir/rndstream
fi

if [ ! yes ]; then
   echo "Installing rndstream"
   cp $pdir/rndstream/rndstream $PREFIX/bin
   chmod +x $PREFIX/bin/rndstream
fi

if [ ! yes ]; then
echo "Downloading mechanizm"
git clone https://github.com/dankozitza/mechanizm ~/m;
fi

