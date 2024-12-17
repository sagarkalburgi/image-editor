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

enum ActionName {
	EdgeAction,
	ThresholdAction,
	SplitAction,
	PaintAction,
	UnknownAction
};