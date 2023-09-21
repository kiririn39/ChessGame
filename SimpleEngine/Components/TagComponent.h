//
// Created by Vlad Boroday on 2023-09-21.
//

#ifndef CHESSGAME_SIMPLEENGINE_COMPONENTS_TAGCOMPONENT_H_
#define CHESSGAME_SIMPLEENGINE_COMPONENTS_TAGCOMPONENT_H_

#include <string>

struct TagComponent
{
	std::string Tag;

	TagComponent() = default;
	TagComponent(const TagComponent&) = default;
	TagComponent(std::string& tag)
		: Tag(tag)
	{
	}
};

#endif //CHESSGAME_SIMPLEENGINE_COMPONENTS_TAGCOMPONENT_H_
