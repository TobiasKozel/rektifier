#include "./DistrhoPluginInfo.h"
#include "DistrhoUI.hpp"
#include "Color.hpp"
#include "src/DistrhoUIPrivateData.hpp"

START_NAMESPACE_DISTRHO

using DGL_NAMESPACE::Color;
using DGL_NAMESPACE::GraphicsContext;
using DGL_NAMESPACE::Rectangle;

// -----------------------------------------------------------------------------------------------------------

class PluginUI : public UI {
public:

	/* constructor */
	PluginUI() : UI(DISTRHO_UI_DEFAULT_WIDTH, DISTRHO_UI_DEFAULT_HEIGHT) {
		// loadSharedResources();
		setGeometryConstraints(128, 128, true);
	}

protected:

	void parameterChanged(uint32_t index, float value) override {
		(void)(index);
		(void)(value);
		repaint();
	}


   /* --------------------------------------------------------------------------------------------------------
	* Widget Callbacks */

	/**
	  The OpenGL drawing function.
	  This UI will draw a 3x3 grid, with on/off states according to plugin state.
	*/
	void onDisplay() override {
		const GraphicsContext& context(getGraphicsContext());
		const uint width = getWidth();
		const uint height = getHeight();
		const uint minwh = std::min(width, height);
		Rectangle<double> r;
		r.setWidth(minwh/3 - 6);
		r.setHeight(minwh/3 - 6);
		Color(0.8f, 0.5f, 0.3f).setFor(context);
		r.draw(context);
	}

	// void onNanoDisplay() override {
	// 	Color labelColor;
	// 	labelColor.green = 1.0;
	// 	beginPath();
	// 	rect(0, 0, 20, 20);
	// 	fillColor(labelColor);
	// 	fill();

	// 	beginPath();
	// 	fontSize(14 * 1);
	// 	fillColor(labelColor);
	// 	Rectangle<float> bounds;
	// 	textBounds(0, 0, "test", NULL, bounds);
	// 	float tx = 16;
	// 	float ty = 16;
	// 	textAlign(ALIGN_CENTER | ALIGN_MIDDLE);

	// 	fillColor(255, 255, 255, 255);
	// 	text(tx, ty, "test2", NULL);
	// 	closePath();
	// }

	bool onKeyboard(const KeyboardEvent& ev) override {
		if (ev.mod & kModifierControl && !ev.press) {
			if (ev.key == 'c') {
			}
			return true;
		}
	}


	/**
	  Mouse press event.
	  This UI will de/activate blocks when you click them and report it as a state change to the plugin.
	*/
	bool onMouse(const MouseEvent& ev) override {
		// Test for left-clicked + pressed first.
		if (ev.button != 1 || ! ev.press)
			return false;

		const uint width = getWidth();
		const uint height = getHeight();

		Rectangle<double> r;

		r.setWidth(width/3 - 6);
		r.setHeight(height/3 - 6);

		// handle left, center and right columns
		for (int i=0; i<3; ++i)
		{
			r.setX(3 + i*width/3);

			// top
			r.setY(3);

			if (r.contains(ev.pos))
			{
				// index that this block applies to
				const uint32_t index = 0+i;

				// invert block state
				fParamGrid[index] = !fParamGrid[index];


				// trigger repaint
				repaint();
				break;
			}

			// middle
			r.setY(3 + height/3);

			if (r.contains(ev.pos))
			{
				// same as before
				const uint32_t index = 3+i;
				fParamGrid[index] = !fParamGrid[index];
				repaint();
				break;
			}

			// bottom
			r.setY(3 + height*2/3);

			if (r.contains(ev.pos))
			{
				// same as before
				const uint32_t index = 6+i;
				fParamGrid[index] = !fParamGrid[index];
				repaint();
				break;
			}
		}

		return true;
	}

	// -------------------------------------------------------------------------------------------------------

private:
	/**
	  Our states used to display the grid.
	  The host does not know about these.
	*/
	bool fParamGrid[9];

	/**
	  Set our UI class as non-copyable and add a leak detector just in case.
	*/
	DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginUI)
};

UI* createUI() { return new PluginUI(); }

END_NAMESPACE_DISTRHO