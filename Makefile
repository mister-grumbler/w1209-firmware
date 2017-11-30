##
## Slightly corrected version of auto generated makefile by CodeLite IDE
##
## Build variables
ProjectName            :=thermostat
SourceDirectory        :=.
BuildDirectory         :=./Build
ObjectSuffix           :=.rel
IncludeSwitch          :=-I
LibrarySwitch          :=-l stm8
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
SourceSwitch           :=-c 
LinkerName             :=/usr/bin/sdcc
LinkOptions            := --out-fmt-ihx -mstm8
OutputFile             :=$(BuildDirectory)/$(ProjectName).ihx
ObjectSwitch           :=-o 
MakeDirCommand         :=mkdir -p
IncludePath            := $(IncludeSwitch). 

##
## Common variables
## CC and CFLAGS can be overriden using an environment variables
##
CC       := /usr/bin/sdcc
CFLAGS   := $(LibrarySwitch) -mstm8


##
## User defined environment variables
##
Objects=$(BuildDirectory)/ts.c$(ObjectSuffix) $(BuildDirectory)/display.c$(ObjectSuffix) $(BuildDirectory)/timer.c$(ObjectSuffix) $(BuildDirectory)/buttons.c$(ObjectSuffix) $(BuildDirectory)/adc.c$(ObjectSuffix) $(BuildDirectory)/menu.c$(ObjectSuffix) $(BuildDirectory)/params.c$(ObjectSuffix) $(BuildDirectory)/relay.c$(ObjectSuffix) 

##
## Main Build Targets 
##
.PHONY: all clean MakeBuildDirectory
all: $(OutputFile)

$(OutputFile): $(BuildDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(BuildDirectory)/.d
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LinkOptions)

MakeBuildDirectory:
	@test -d $(BuildDirectory) || $(MakeDirCommand) $(BuildDirectory)

$(BuildDirectory)/.d:
	@test -d $(BuildDirectory) || $(MakeDirCommand) $(BuildDirectory)

##
## Objects
##
$(BuildDirectory)/ts.c$(ObjectSuffix): ts.c
	$(CC) $(SourceSwitch) "$(SourceDirectory)/ts.c" $(CFLAGS) $(ObjectSwitch)$(BuildDirectory)/ts.c$(ObjectSuffix) $(IncludePath)

$(BuildDirectory)/display.c$(ObjectSuffix): display.c
	$(CC) $(SourceSwitch) "$(SourceDirectory)/display.c" $(CFLAGS) $(ObjectSwitch)$(BuildDirectory)/display.c$(ObjectSuffix) $(IncludePath)

$(BuildDirectory)/timer.c$(ObjectSuffix): timer.c
	$(CC) $(SourceSwitch) "$(SourceDirectory)/timer.c" $(CFLAGS) $(ObjectSwitch)$(BuildDirectory)/timer.c$(ObjectSuffix) $(IncludePath)

$(BuildDirectory)/buttons.c$(ObjectSuffix): buttons.c
	$(CC) $(SourceSwitch) "$(SourceDirectory)/buttons.c" $(CFLAGS) $(ObjectSwitch)$(BuildDirectory)/buttons.c$(ObjectSuffix) $(IncludePath)

$(BuildDirectory)/adc.c$(ObjectSuffix): adc.c
	$(CC) $(SourceSwitch) "$(SourceDirectory)/adc.c" $(CFLAGS) $(ObjectSwitch)$(BuildDirectory)/adc.c$(ObjectSuffix) $(IncludePath)

$(BuildDirectory)/menu.c$(ObjectSuffix): menu.c
	$(CC) $(SourceSwitch) "$(SourceDirectory)/menu.c" $(CFLAGS) $(ObjectSwitch)$(BuildDirectory)/menu.c$(ObjectSuffix) $(IncludePath)

$(BuildDirectory)/params.c$(ObjectSuffix): params.c
	$(CC) $(SourceSwitch) "$(SourceDirectory)/params.c" $(CFLAGS) $(ObjectSwitch)$(BuildDirectory)/params.c$(ObjectSuffix) $(IncludePath)

$(BuildDirectory)/relay.c$(ObjectSuffix): relay.c
	$(CC) $(SourceSwitch) "$(SourceDirectory)/relay.c" $(CFLAGS) $(ObjectSwitch)$(BuildDirectory)/relay.c$(ObjectSuffix) $(IncludePath)


##
## Clean
##
clean:
	$(RM) -r $(BuildDirectory)/


