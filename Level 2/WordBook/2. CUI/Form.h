#pragma once
#ifndef _FORM_H
#define _FORM_H

typedef struct _wordBook WordBook;

void DisplayMenu();
void FormForRecording(WordBook *wordBook);
void FormForFinding(WordBook *wordBook);
void FormForCorrecting(WordBook *wordBook);
void FormForErasing(WordBook *wordBook);
void FormForArranging(WordBook *wordBook);
void FormForView(WordBook *wordBook);

#endif