#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "TestShooter/HealthSystem/HealthSystem.h"
#include "PlayerHealthWidget.generated.h"

UCLASS()
class TESTSHOOTER_API UPlayerHealthWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UProgressBar* HealthBar;
	
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION(BlueprintCallable)
	void UpdateView();

	UFUNCTION(BlueprintCallable)
	void HealthSystemChanged(UHealthSystem* healthSystem);

	UFUNCTION()
	void PlayerSpawned(AActor* playerActor);
	
private:
	UPROPERTY(VisibleAnywhere)
	UHealthSystem* HealthSystem;
};
