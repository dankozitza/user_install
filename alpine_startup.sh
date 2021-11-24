# alpine_startup.sh

if [  yes ]; then
	echo "script must be configured";
	exit;
fi

echo "Installing applications"
#sudo apk add screen
#sudo apk add vim
#sudo apk add git
#sudo apk add make
#sudo apk add gcc

if [ ! yes ]; then
echo "Configuring git"
git config --system user.name "dankozitza"
git config --system user.email "dankoz@gmx.us"
git config --system color.diff always
git config --system color.status true
git config --system credential.helper store
fi

if [ ! yes ]; then
echo "Installing mechanizm libs"
sudo apk add freeglut-dev
sudo apk add jsoncpp-dev
sudo apk add glm-dev
fi

if [ ! yes ]; then
echo "Installing mechanizm"
git clone https://github.com/dankozitza/mechanizm ~/m;
fi
