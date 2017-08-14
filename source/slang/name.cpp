// name.cpp
#include "name.h"

namespace Slang {

String getText(Name* name)
{
    if (!name) return String();
    return name->text;
}

Name* NamePool::getName(String const& text)
{
    RefPtr<Name> name;
    if (rootPool->names.TryGetValue(text, name))
        return name;

    name = new Name();
    name->text = text;
    rootPool->names.Add(text, name);
    return name;
}

} // namespace Slang
