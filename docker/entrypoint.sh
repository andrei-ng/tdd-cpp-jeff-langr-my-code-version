#! /bin/bash
set -e

if [ -f "$HOME/.zshrc" ]; then
	cat $HOME/.bash_aliases >> $HOME/.zshrc
	echo "" >> $HOME/.zshrc
fi

# Add QTcreator alias command
if [ -d "$HOME/Qt" ]; then
	echo "" >> $HOME/.bash_aliases
	echo "alias qtcreator=$HOME/Qt/Tools/QtCreator/bin/qtcreator" >> $HOME/.bash_aliases
	echo "" >> $HOME/.bash_aliases

	echo "alias qtcreator=$HOME/Qt/Tools/QtCreator/bin/qtcreator" >> $HOME/.zshrc
fi

# Change owner of copied example
if [ -d "$HOME/gtest_cmake_module_based_example" ]; then
	sudo chown -R $USER:$USER $HOME/gtest_cmake_module_based_example
fi

exec "$@"

