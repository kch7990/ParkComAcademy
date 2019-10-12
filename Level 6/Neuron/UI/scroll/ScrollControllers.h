#ifndef _SCROLLCONTROLLER_H
#define _SCROLLCONTROLLER_H

typedef signed long int Long;
class Scroll;

class ScrollController {
public:
	ScrollController();
	ScrollController(const ScrollController& source);
	virtual ~ScrollController() = 0;

	virtual void Update() = 0;
	
	Long Up();
	Long Down();
	Long PageUp();
	Long PageDown();
	Long Move(Long position);
	Long Rotate(short delta);

	Scroll* GetScroll() const;
	Long GetWidth() const;
	Long GetHeight() const;

	ScrollController& operator=(const ScrollController& source);
protected:
	Scroll *scroll;
	Long width;
	Long height;
};

inline Scroll* ScrollController::GetScroll() const {
	return const_cast<Scroll*>(this->scroll);
}

inline Long ScrollController::GetWidth() const {
	return this->width;
}

inline Long ScrollController::GetHeight() const {
	return this->height;
}

//NeuralNetworkFormScrollController
class NeuralNetworkForm;

class NeuralNetworkFormScrollController : public ScrollController {
public:
	NeuralNetworkFormScrollController(NeuralNetworkForm *neuralNetworkForm = 0);
	NeuralNetworkFormScrollController(const NeuralNetworkFormScrollController& source);
	virtual ~NeuralNetworkFormScrollController();

	virtual void Update();

	NeuralNetworkFormScrollController& operator=(const NeuralNetworkFormScrollController& source);
private:
	NeuralNetworkForm *neuralNetworkForm;
};

//LayerInformationFormScrollController
class LayerInformationForm;

class LayerInformationFormScrollController : public ScrollController {
public:
	LayerInformationFormScrollController(LayerInformationForm *layerInformationForm = 0);
	LayerInformationFormScrollController(const LayerInformationFormScrollController& source);
	virtual ~LayerInformationFormScrollController();

	virtual void Update();

	LayerInformationFormScrollController& operator=(const LayerInformationFormScrollController& source);
private:
	LayerInformationForm *layerInformationForm;
};


#endif //_SCROLLCONTROLLER_H