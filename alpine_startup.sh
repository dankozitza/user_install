# alpine_startup.sh

if [  yes ]; then
	echo "script must be configured";
	exit;
fi

echo "Installing applications"
#sudo apk add screen
#sudo apk add vim
#sudo apk add make
#sudo apk add gcc

if [ ! yes ]; then
	git config --system user.name "Dan Kozitza";
	git config --system user.email "dankoz@gmx.us";
	git config --system color.diff always;
	git config --system color.status true;
fi

echo "Installing mechanizm includes"
#sudo apk add freeglut-dev
#sudo apk add jsoncpp-dev
#sudo apk add glm-dev

