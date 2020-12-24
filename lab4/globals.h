#include <iostream>
using namespace std;
#include<string>

// These arrays should make it easier to check that a name is not a reserved word
// and that an entered shape type is valid
#define NUM_KEYWORDS 6
string keyWordsList[NUM_KEYWORDS]={"shape", "group", "move", "delete", "draw", "pool"};

#define NUM_TYPES 3
string shapeTypesList[NUM_TYPES]={"ellipse", "rectangle","triangle"};
#endif /* globals_h */

