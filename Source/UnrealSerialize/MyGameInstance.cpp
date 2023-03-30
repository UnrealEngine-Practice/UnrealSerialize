// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	
}

void UMyGameInstance::Init()
{
	Super::Init();
	FStudentData RawDataSrc(11, TEXT("abc"));

	// 저장할 파일의 위치
	const FString SavedDir = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));
	UE_LOG(LogTemp, Log, TEXT("저장할 파일위치 : %s"), *SavedDir);

	{
		const FString RawDataFilename(TEXT("RawData.bin"));
		FString RawDataAbsolutePath = FPaths::Combine(*SavedDir, *RawDataFilename);
		UE_LOG(LogTemp, Log, TEXT("저장할 파일 절대경로 : %s"), *RawDataAbsolutePath);

		FPaths::MakeStandardFilename(RawDataAbsolutePath);
		UE_LOG(LogTemp, Log, TEXT("저장할 파일 절대경로 : %s"), *RawDataAbsolutePath);
		
		// Ar는 Archive라는 뜻 ㅎ
		// 전달해준 Path에 write할 수 있는 아카이브 객체 생성됨.
		FArchive* RawFileWriterAr = IFileManager::Get().CreateFileWriter(*RawDataAbsolutePath);
		if (RawFileWriterAr != nullptr)
		{
			*RawFileWriterAr << RawDataSrc;
			RawFileWriterAr->Close();
			delete RawFileWriterAr;
			RawFileWriterAr = nullptr;

			// UE_LOG(LogTemp, Log, TEXT("[RawData] 이름 %s 순번 %d"), *RawDa);
		}
		FStudentData RawDataDest;
		FArchive* RawFileReaderAr = IFileManager::Get().CreateFileReader(*RawDataAbsolutePath);
		if (RawFileReaderAr != nullptr)
		{
			// << 연산자라 입력 같지만, Reader에 대한 << 연산자는 Reader에서 Dest로 쓴다.
			*RawFileReaderAr << RawDataDest;
			RawFileReaderAr->Close();
			delete RawFileReaderAr;
			RawFileReaderAr = nullptr;

			UE_LOG(LogTemp, Log, TEXT("[RawData] 이름 %s 순번 %d"), *RawDataDest.Name, RawDataDest.Order);
		}
		
	}
}
