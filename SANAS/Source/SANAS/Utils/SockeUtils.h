#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"


namespace SocketUtils
{
	inline TOptional<FTransform> GetSocketTransform(const USceneComponent* Component, const FName Socket)
	{
		return IsValid(Component) && !Socket.IsNone() && Component->DoesSocketExist(Socket) ? Component->GetSocketTransform(Socket) : TOptional<FTransform>();
	}

	inline TOptional<float> GetDistanceBetweenSockets(const USceneComponent* Component, const FName FromSocket, const  FName ToSocket)
	{
		if (const TOptional<FTransform> From =  GetSocketTransform(Component, FromSocket))
		{
			if (const TOptional<FTransform> To = GetSocketTransform(Component, ToSocket))
			{
				return FVector::Distance(From->GetLocation(), To->GetLocation());
			}
		}
		return NullOpt;
	}
}
