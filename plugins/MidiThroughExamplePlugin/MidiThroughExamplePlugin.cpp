/*
 * DISTRHO Plugin Framework (DPF)
 * Copyright (C) 2012-2018 Filipe Coelho <falktx@falktx.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include "DistrhoPlugin.hpp"
#include <iostream> // std::cout
#include <string>
#include <typeinfo> // operator typeid

START_NAMESPACE_DISTRHO

    // -----------------------------------------------------------------------------------------------------------

    /**
      Plugin that demonstrates MIDI output in DPF.
     */
    class MidiThroughExamplePlugin : public Plugin {
public:
    MidiThroughExamplePlugin()
        : Plugin(0, 0, 0) {}

protected:
   /* --------------------------------------------------------------------------------------------------------
    * Information */

   /**
      Get the plugin label.
      This label is a short restricted name consisting of only _, a-z, A-Z and 0-9 characters.
    */
    const char* getLabel() const override
    {
        return "MidiThrough";
    }

   /**
      Get an extensive comment/description about the plugin.
    */
    const char* getDescription() const override
    {
        return "Plugin that demonstrates MIDI output in DPF.";
    }

   /**
      Get the plugin author/maker.
    */
    const char* getMaker() const override
    {
        return "DISTRHO";
    }

   /**
      Get the plugin homepage.
    */
    const char* getHomePage() const override
    {
        return "https://github.com/DISTRHO/DPF";
    }

   /**
      Get the plugin license name (a single line of text).
      For commercial plugins this should return some short copyright information.
    */
    const char* getLicense() const override
    {
        return "ISC";
    }

   /**
      Get the plugin version, in hexadecimal.
    */
    uint32_t getVersion() const override
    {
        return d_version(1, 0, 0);
    }

   /**
      Get the plugin unique Id.
      This value is used by LADSPA, DSSI and VST plugin formats.
    */
    int64_t getUniqueId() const override
    {
        return d_cconst('d', 'M', 'T', 'r');
    }

   /* --------------------------------------------------------------------------------------------------------
    * Init and Internal data, unused in this plugin */

    void  initParameter(uint32_t, Parameter&) override {}
    float getParameterValue(uint32_t) const   override { return 0.0f;}
    void  setParameterValue(uint32_t, float)  override {}

   /* --------------------------------------------------------------------------------------------------------
    * Audio/MIDI Processing */

   /**
      Run/process function for plugins with MIDI input.
      In this case we just pass-through all MIDI events.
    */
    void run(const float**, float**, uint32_t,
             const MidiEvent* midiEvents, uint32_t midiEventCount) override
    {

      // int status = midiEvents[0].data[0];

      // char str[200];
      // sprintf(str, "My str : %02u", status);
      // std::cout << str << '\n';

      for (uint32_t i = 0; i < midiEventCount; ++i)
	{

	  // d0 after touch
	  // 90 note press
	  // 80 note release
	  if ( midiEvents[i].size > MidiEvent::kDataSize ){


	    printf("status ext: %02x\n", (midiEvents[i].dataExt[0] & 0xF0));
	    printf("note: %02x\n", midiEvents[i].dataExt[1]);
	    printf("3nd: %02x\n", midiEvents[i].dataExt[2]);
	    printf("4nd: %02x\n", midiEvents[i].dataExt[3]);
	    printf("5nd: %02x\n", midiEvents[i].dataExt[4]);
	    printf("6nd: %02x\n", midiEvents[i].dataExt[6]);

	  }
	  else {
	    int status = midiEvents[i].data[0] & 0xF0;
	    int keyNote = midiEvents[i].data[1];
	    int value = midiEvents[i].data[2];
	    printf("status: %02x\n", (midiEvents[i].data[0] & 0xF0));
	    printf("key/note: %02x\n", midiEvents[i].data[1]);
	    printf("value: %02x\n", midiEvents[i].data[2]);

	    printf("-------\n" );
	    // if the value == 13 it's the Z axis
	    if ( keyNote == 0x62  ) {


	      if (value == 0x11) {
		printf("Axe x" );
	      }


	      if (value == 0x12) {
		printf("Axe y" );
	      }


	      if (value == 0x13) {
		printf("Axe z" );
	      }
	      printf("\n" );
	      i++;
	      uint32_t lsbValue = midiEvents[i++].data[2];

	      uint32_t msbValue = (midiEvents[i++].data[2] +1 )*127;
	      int msbLsbValue  = msbValue + lsbValue - 1;
	      printf("msb value: %i\n", msbValue  );
	      printf("lsb value: %i\n", lsbValue  );
	      printf("msb/lsb value: %i\n", msbLsbValue  );

	    }

	    // printf("ext1: %02x\n", midiEvents[i].dataExt[0]);
	    // printf("ext2: %02x\n", midiEvents[i].dataExt[1]);
	    // printf("ext3: %02x\n", midiEvents[i].dataExt[2]);
	    // printf("ext4: %02x\n", midiEvents[i].dataExt[4]);
	    // printf("4nd: %02x\n", midiEvents[i].data[3]);
	    // printf("5nd: %02x\n", midiEvents[i].data[4]);
	    // printf("6nd: %02x\n", midiEvents[i].data[5]);
	    // printf("7nd: %02x\n", midiEvents[i].data[6]);
	    // printf("8nd: %02x\n", midiEvents[i].data[7]);
	    // printf("9nd: %02x\n", midiEvents[i].data[8]);
	    // printf("10nd: %02x\n", midiEvents[i].data[9]);
	    // printf("11nd: %02x\n", midiEvents[i].data[10]);
	    // printf("12nd: %02x\n", midiEvents[i].data[11]);

	    // printf("status: %02x\n", (midiEvents[i].data[0] & 0xF0));
	    // printf("key/note: %02x\n", midiEvents[i].data[1]);


	  }



	}

    }


    // -------------------------------------------------------------------------------------------------------

private:
    // nothing here :)

   /**
      Set our plugin class as non-copyable and add a leak detector just in case.
    */
    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiThroughExamplePlugin)
};

/* ------------------------------------------------------------------------------------------------------------
 * Plugin entry point, called by DPF to create a new plugin instance. */

Plugin* createPlugin()
{
    return new MidiThroughExamplePlugin();
}

// -----------------------------------------------------------------------------------------------------------G

END_NAMESPACE_DISTRHO
