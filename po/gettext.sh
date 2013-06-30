# sh script to generate catalog file
# it searches for strings marked with _() or tr() in all .cpp and .h files in directory
# the generated file is called 'EyesWatcher.pot' and is generated in ./po
pushd ${0%[\\/]*}
FILE_LIST=`{ find ../src -name '*.cpp' -print && find ../include -name '*.h' -print; }`
xgettext -d EyesWatcher -s --keyword=tr --keyword=_ -p . -o EyesWatcher.pot $FILE_LIST
popd
