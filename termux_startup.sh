# termux_startup.sh

if [  yes ]; then
	echo "script must be configured";
	exit;
fi

if [ ! yes ]; then
echo "Installing applications"
pkg install screen
pkg install vim
pkg install clang
pkg install make

echo "Configuring applications"
#cp userhome/.bashrc ~
cp userhome/.vimrc ~
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
pkg install jsoncpp
mkdir p
git clone https://github.com/dankozitza/rndstream p
cd p/rndstream; make;
fi

if [ ! yes ]; then
echo "Installing mechanizm"
git clone https://github.com/dankozitza/mechanizm ~/m;
fi
