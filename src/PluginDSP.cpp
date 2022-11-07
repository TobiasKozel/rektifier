#include "DistrhoPlugin.hpp"

#include <cassert>


#include "../GuitarD/src/headless/compile_unit/GHeadlessUnit.h"
#include "../resources/preset.h"

#ifndef MIN
	#define MIN(a,b) ( (a) < (b) ? (a) : (b) )
#endif

#ifndef MAX
	#define MAX(a,b) ( (a) > (b) ? (a) : (b) )
#endif

#ifndef CLAMP
	#define CLAMP(v, min, max) (MIN((max), MAX((min), (v))))
#endif

#ifndef DB_CO
	#define DB_CO(g) ((g) > -90.0f ? powf(10.0f, (g) * 0.05f) : 0.0f)
#endif

#define DB_MIN -90.f
#define DB_MAX 30.f

START_NAMESPACE_DISTRHO

class PluginDSP : public Plugin {

public:
	PluginDSP() : Plugin(kNumParams, 0, 0) {
		auto rate = getSampleRate();
		// if we get a problematic/zero rate just pretend we're at 48000 until the daw reports a proper one
		if (rate < 10000) { rate = 48000; }
		mGuitard.setConfig(getSampleRate(), 2, 2);
		// but we'll need a rate to lead the preset in advace
		mGuitard.load(preset);
	}

protected:
	void initParameter(uint32_t index, Parameter& parameter) override {
		parameter.hints = kParameterIsAutomatable; // all of them are automateable
		parameter.ranges.min = 0.f;
		parameter.ranges.max = 100.f;
		switch (index) {
			case kParamGate:
				parameter.ranges.min = DB_MIN;
				parameter.ranges.max = DB_MAX;
				parameter.ranges.def = mGate;
				parameter.name = "Noise Gate";
				parameter.shortName = "Gate";
				parameter.symbol = "gate";
				parameter.unit = "dB";
				break;
			case kParamGain:
				parameter.ranges.min = DB_MIN;
				parameter.ranges.max = DB_MAX;
				parameter.ranges.def = mGain;
				parameter.name = "Pre Gain";
				parameter.shortName = "gain";
				parameter.symbol = "gain";
				parameter.unit = "dB";
				break;
			case kParamWidth:
				parameter.ranges.def = mWidth;
				parameter.name = "Stereo Width";
				parameter.shortName = "Width";
				parameter.symbol = "width";
				break;
			case kParamCab:
				parameter.ranges.def = mCab;
				parameter.name = "Guitar Cab Mix";
				parameter.shortName = "Cab";
				parameter.symbol = "cab";
				break;
			case kParamRekt:
				parameter.ranges.def = mRekt;
				parameter.name = "Rekt";
				parameter.shortName = "Rekt";
				parameter.symbol = "rekt";
				break;
			case kParamSag:
				parameter.ranges.def = mSag;
				parameter.name = "Amplifier Sag";
				parameter.shortName = "Sag";
				parameter.symbol = "sag";
				break;
			case kParamInput:
				parameter.ranges.def = mInput;
				parameter.name = "Input channels (L/R/L+R)";
				parameter.shortName = "Input";
				parameter.symbol = "input";
				break;
			default:
				assert(false);
				return;
		}
	}

	float getParameterValue(uint32_t index) const override {
		switch (index) {
			case kParamGate:	return mGate;
			case kParamGain:	return mGain;
			case kParamWidth:	return mWidth;
			case kParamCab:		return mCab;
			case kParamRekt:	return mRekt;
			case kParamSag:		return mSag;
			case kParamInput:	return mInput;
		}
		assert(false);
		return 0.f;
	}

	void setParameterValue(uint32_t index, float value) override {
		switch (index) {
			case kParamGate:	mGate	= value; break;
			case kParamGain:	mGain	= value; break;
			case kParamWidth:	mWidth	= value; break;
			case kParamCab:		mCab	= value; break;
			case kParamRekt:	mRekt	= value; break;
			case kParamSag:		mSag	= value; break;
			case kParamInput:	mInput	= value; break;
			default:
				assert(false);
				break;
		}
	}

	void activate() override {
		mGuitard.reset();
	}

	void sampleRateChanged(double newSampleRate) override {
		if (1000 < newSampleRate) {
			mGuitard.setConfig(newSampleRate, 2, 1);
		}
	}

	void run(const float** inputs, float** outputs, uint32_t frames) override {
		const int channelsOut = 2; // todo maybe there's mono output?
		if (outputs == nullptr) { return; }
		
		if (inputs == nullptr) {
			for (int c = 0; c < channelsOut; c++) {
				for (int i = 0; i < frames; i++) {
					outputs[c][i] = 0.0;
				}
			}
		}
		
		{
			// TODO in channel handling
			// const double left = mInput > 33.f;
			// const double right = 66.f > mInput;

			// if (left && !right) {
			// 	for (int i = 0; i < frames; i++) {
			// 		inputs[1][i] = inputs[0][i];
			// 	}
			// }
			// if (right && !left) {
			// 	for (int i = 0; i < frames; i++) {
			// 		inputs[0][i] = inputs[1][i];
			// 	}
			// }
		}

		mGuitard.setParam(36, mCab / 100.f);
		mGuitard.setParam(46, mSag / 100.f);
		
		const double gain = DB_CO(CLAMP(mGain, DB_MIN, DB_MAX));
		mGuitard.setParam(33, gain);
		
		const float gate = DB_CO(CLAMP(mGate, DB_MIN, DB_MAX));
		mGuitard.setParam(52, gate);
		
		const float rekt = mRekt / 100.f;
		const float width = mWidth / 100.f;

		float pan1;
		float pan2;
		float mix;
		if (rekt <= 0.5) {
			pan1 = -rekt + 0.5;
			pan2 = 1.0;
			mix = rekt * 1.6;
		} else {
			pan1 = 0.0;
			pan2 = -0.6 * rekt + 1.3;
			mix = rekt * 0.4 + 0.6;
		}

		mGuitard.setParam(20, pan1);
		mGuitard.setParam(21, pan2);
		mGuitard.setParam(22, mix);
		mGuitard.setParam(74, width * 0.9);
		mGuitard.setParam(72, CLAMP(float(1.0 - width * 0.5), 0.5f, 1.0f));

		mGuitard.process(const_cast<const float**>(inputs), outputs, frames);

		for (int c = 0; c < channelsOut; c++) {
			for (int i = 0; i < frames; i++) {
			outputs[c][i] *= 0.5;
			}
		}
		
	}

	#pragma region Plugin Metadata

	int64_t getUniqueId() const override { return d_cconst('r', 'e', 'k', 't'); }
	const char* getLicense() const override { return DISTRHO_PLUGIN_LICENSE; }
	const char* getHomePage() const override { return DISTRHO_PLUGIN_URI; }
	const char* getLabel() const override { return DISTRHO_PLUGIN_NAME; }
	const char* getMaker() const override { return DISTRHO_PLUGIN_BRAND; }
	const char* getDescription() const override {
		return "Node-Based effects processor for electric guitars.";
	}
	uint32_t getVersion() const override {
		return d_version(
			DISTRHO_PLUGIN_VERSION_MAJOR,
			DISTRHO_PLUGIN_VERSION_MINOR,
			DISTRHO_PLUGIN_VERSION_PATCH
		);
	}

	#pragma endregion

	DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginDSP)

private:
	guitard::GuitarDHeadless mGuitard;
	float mGate = -70.0f;
	float mGain = 0.f;
	float mWidth = 50.f;
	float mCab = 100.f;
	float mRekt = 50.f;
	float mSag = 59.67f;
	float mInput = 0.f;
};

Plugin* createPlugin() { return new PluginDSP(); }

END_NAMESPACE_DISTRHO
