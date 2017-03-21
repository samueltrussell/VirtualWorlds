// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "WallJumper2.h"
#include "WallJumper2GameMode.h"
#include "WallJumper2Character.h"

AWallJumper2GameMode::AWallJumper2GameMode()
{
	// set default pawn class to our character
	DefaultPawnClass = AWallJumper2Character::StaticClass();	
}
