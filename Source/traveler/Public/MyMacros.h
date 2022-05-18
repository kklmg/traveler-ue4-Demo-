// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#define DECLARE_CONST_FNAME(Name) const FName Name(TEXT(#Name)); 
#define DECLARE_NAMESPACE_CONST_FNAME(NameSpace) namespace NameSpace{ const FName Name(TEXT(#NameSpace));};
#define DECLARE_NAMESPACE_CONST_FNAME_DATACLASS(NameSpace, DataClass)  namespace NameSpace{ const FName Name(TEXT(#NameSpace)); typedef DataClass Type;};

