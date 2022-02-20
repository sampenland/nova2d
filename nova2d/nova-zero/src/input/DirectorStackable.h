#pragma once

namespace novazero
{
	namespace input
	{
		class DirectorStackable
		{

		protected:
			DirectorStackable() {};

		public:

			int m_TabIndex = 0;
			bool m_Selected = false;

			virtual void Update() = 0;
			virtual void Select(bool isSelected, const std::string& fillColor, const std::string& outlineColor) = 0;

			virtual void SetEnabled(bool v) = 0;
			virtual void SetVisible(bool v) = 0;

		};
	}
}