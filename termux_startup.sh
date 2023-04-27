# termux_startup.sh

pdir="$HOME/p"

if [ ! yes ]; then
	echo "script must be configured";
	exit;
fi

if [ ! yes ]; then
echo "Installing applications"
pkg install screen
pkg install vim
pkg install clang
pkg install make
pkg install jsoncpp

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
echo "Installing rndstream"
mkdir $pdir
git clone https://github.com/dankozitza/rndstream $pdir/rndstream
make -C $pdir/rndstream;
fi

if [ ! yes ]; then
echo "Installing mechanizm"
git clone https://github.com/dankozitza/mechanizm ~/m;
fi


