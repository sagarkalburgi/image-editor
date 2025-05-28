#pragma once
#include <QStringList>

QStringList MenuOptions = {
	"Edge", 
	"Threshold", 
	"Split",
	"Paint"
};

QStringList MenuMain = {
	"Open",
	"Save",
	"Exit"
};

QStringList MenuHelp = {
	"Info",
	"Version",
	"Tutorial"
};

enum ActionName {
	EdgeAction,
	ThresholdAction,
	SplitAction,
	PaintAction,
	InfoAction,
	VersionAction,
	TutorialAction,
	UnknownAction
};