/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "twp/gfx.h"
#include "twp/object.h"
#include "twp/scenegraph.h"

#define MAX_VERBS 22
#define NUMACTORS 6

#ifndef TWP_HUD_H
#define TWP_HUD_H

namespace Twp {

struct VerbUiColors {
	Color sentence;
	Color verbNormal;
	Color verbNormalTint;
	Color verbHighlight;
	Color verbHighlightTint;
	Color dialogNormal;
	Color dialogHighlight;
	Color inventoryFrame;
	Color inventoryBackground;
	Color retroNormal;
	Color retroHighlight;

	VerbUiColors();
	VerbUiColors(Color s, Color vbNormal, Color vbNormalTint, Color vbHiglight, Color vbHiglightTint, Color dlgNormal, Color dlgHighlt, Color invFrame, Color inventoryBack, Color retroNml, Color retroHighlt);
};

struct Verb {
	VerbId id;
	Common::String image;
	Common::String fun;
	Common::String text;
	Common::String key;
	int flags{};

	Verb();
	Verb(VerbId id, const Common::String &image, const Common::String &fun, const Common::String &text, const Common::String &key, int flags = 0);
};

struct ActorSlot {
public:
	VerbUiColors verbUiColors;
	Verb verbs[MAX_VERBS];
	bool selectable = false;
	Common::SharedPtr<Object> actor;

public:
	ActorSlot();

	Verb *getVerb(int id) {
		for (auto &verb : verbs) {
			if (verb.id.id == id) {
				return &verb;
			}
		}
		return nullptr;
	}
};

class Hud;
struct VerbRect {
	Hud *hud;
	int index;
};

class HudShader : public Shader {
public:
	HudShader();
	~HudShader() override;

	void init();

private:
	void applyUniforms() final;

public:
	Color _shadowColor;
	Color _normalColor;
	Color _highlightColor;
};

class Hud : public Node {
public:
	Hud();

	void init();
	ActorSlot *actorSlot(Common::SharedPtr<Object> actor);
	bool isOver() const { return _over; }
	void update(float elapsed, Math::Vector2d pos, Common::SharedPtr<Object> hotspot, bool mouseClick);

	void setVisible(bool visible) override;

private:
	void drawCore(Math::Matrix4 trsf) final;
	void drawSprite(const SpriteSheetFrame &sf, Texture *texture, Color color, Math::Matrix4 trsf);

public:
	ActorSlot _actorSlots[NUMACTORS];
	Common::SharedPtr<Object> _actor;
	Verb _verb;
	HudShader _shader;
	Math::Vector2d _mousePos;
	bool _mouseClick = false;
	bool _over = false;
	int _defaultVerbId = 0;
	float _fadeTime = 0.f;
	bool _fadeIn = false;
};
} // namespace Twp

#endif
