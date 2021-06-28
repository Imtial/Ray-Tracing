class_name=$1
file_name=${class_name,}

include="include/$file_name.hpp"
src="src/$file_name.cpp"

mkdir -p include src

header_template="#ifndef ${class_name^^}_H
#define ${class_name,^^}_H

class $class_name
{
    private:
    public:
        $class_name();
        ~$class_name();
};

#endif"

source_template="#include \"$file_name.hpp\"

$class_name::$class_name()
{

}

$class_name::~$class_name()
{

}
"
if [ ! -e $include ] ; then
    echo "$header_template" > $include
    code $include
else 
    echo "$include already exists"
fi

if [ ! -e $src ] ; then
    echo "$source_template" > $src
    code $src
else 
    echo "$src already exists"
fi