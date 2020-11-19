# Overview

## Changes:
Be precise and detailed.
- *insert here*

## Usage
```cpp
#include "pe_exceptions/pe_exception.hpp"

int main() {

    try {
        throw peach::PeachException("asd", 23, "as");
    } catch(const peach::detail::pe_base_exception& ec)
    {
        ec.output_to_file();
        ec.print_to_console();
    }

    return 0;
}
```
### Output
```
Exception occurred on line: 7 in file: C:\Users\joren\CLionProjects\Test Projects\main.cpp.
Error details: asd 23 as 
```

## Any changes on files besides the ones directly connected to your feature/change (emtpy if none):
E.g. if you integrated your feature into the `ExceptionBase`, said change belongs here.
- *insert here*

## Additional Notes:
Anything else one should know about this pull request.
- *insert here*

</br>

# Tests:
- [ ] Test feature thorougly  
- [ ] Compiles w/ clang 11  
- [ ] Formatted according to the .clang-format  

# Extra
- [ ] Add explanation/documentation on wiki/readme page
