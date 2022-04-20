#pragma once
#include "../TimelineEvent.h"
#include "../TimelineInstance.h"

namespace novazero
{
	namespace utils
	{
		namespace timeline
		{
			namespace events
			{
				class TimelineExecuteEvent : public TimelineEvent
				{

				private:

					unsigned int m_ID = 0;

					FuncType f_EventType = FuncType::Undefined;
					std::function<void()> f_EventFuncVoid;

					std::function<void(int, float)> f_EventFuncInt1Float1;
					std::function<void(int, int, float)> f_EventFuncInt2Float1;
					std::function<void(float, float, int)> f_EventFuncFloat2Int1;
					std::function<void(float, float, int, int)> f_EventFuncFloat2Int2;

					std::function<void(float)> f_EventFuncFloat;
					std::function<void(float, float)> f_EventFuncFloat2;

					std::function<void(int)> f_EventFuncInt;
					std::function<void(int, int)> f_EventFuncInt2;

					float m_F1 = 0;
					float m_F2 = 0;
					int m_I1 = 0;
					int m_I2 = 0;

				public:

					TimelineExecuteEvent() {};
					TimelineExecuteEvent(TimelineInstance* instance,
						std::function<bool()> nextEventTrigger, float timeTillNextEventSeconds = 1.f) :
						TimelineEvent(instance, nextEventTrigger, timeTillNextEventSeconds)
					{ 
						m_ID = n2dAddDeleteable(this);
					}

					void SetFunction(std::function<void()> func)
					{
						f_EventType = FuncType::Void;
						f_EventFuncVoid = func;
					}

					void SetFunction(std::function<void(int)> func, int i1)
					{
						f_EventType = FuncType::Int;
						
						m_I1 = i1;
						m_I2 = 0;
						m_F1 = 0.f;
						m_F2 = 0.f;

						f_EventFuncInt = func;
					}

					void SetFunction(std::function<void(float)> func, float f1)
					{
						f_EventType = FuncType::Float;

						m_I1 = 0;
						m_I2 = 0;
						m_F1 = f1;
						m_F2 = 0.f;

						f_EventFuncFloat = func;
					}

					void SetFunction(std::function<void(int, int)> func, int i1, int i2)
					{
						f_EventType = FuncType::Int2;

						m_I1 = i1;
						m_I2 = i2;
						m_F1 = 0.f;
						m_F2 = 0.f;

						f_EventFuncInt2 = func;
					}

					void SetFunction(std::function<void(float, float)> func, float f1, float f2)
					{
						f_EventType = FuncType::Float2;

						m_I1 = 0;
						m_I2 = 0;
						m_F1 = f1;
						m_F2 = f2;

						f_EventFuncFloat2 = func;
					}

					void SetFunction(std::function<void(int, float)> func, int i1, float f1)
					{
						f_EventType = FuncType::Int1Float1;

						m_I1 = i1;
						m_I2 = 0;
						m_F1 = f1;
						m_F2 = 0.f;

						f_EventFuncFloat2 = func;
					}

					void SetFunction(std::function<void(int, int, float)> func, int i1, int i2, float f1)
					{
						f_EventType = FuncType::Int2Float1;

						m_I1 = i1;
						m_I2 = i2;
						m_F1 = f1;
						m_F2 = 0.f;

						f_EventFuncInt2Float1 = func;
					}

					void SetFunction(std::function<void(float, float, int)> func, float f1, float f2, int i1)
					{
						f_EventType = FuncType::Float2Int1;

						m_I1 = i1;
						m_I2 = 0;
						m_F1 = f1;
						m_F2 = f2;

						f_EventFuncFloat2Int1 = func;
					}

					void SetFunction(std::function<void(float, float, int, int)> func, float f1, float f2, int i1, int i2)
					{
						f_EventType = FuncType::Float2Int2;

						m_I1 = i1;
						m_I2 = i2;
						m_F1 = f1;
						m_F2 = f2;

						f_EventFuncFloat2Int2 = func;
					}

					void Execute() override
					{
						switch (f_EventType)
						{
						case FuncType::Undefined:
							return;
						case FuncType::Void:
							f_EventFuncVoid();
							break;
						case FuncType::Float:
							f_EventFuncFloat(m_F1);
							break;
						case FuncType::Float2:
							f_EventFuncFloat2(m_F1, m_F2);
							break;
						case FuncType::Int:
							f_EventFuncInt(m_I1);
							break;
						case FuncType::Int2:
							f_EventFuncInt2(m_I1, m_I2);
							break;
						case FuncType::Float2Int1:
							f_EventFuncFloat2Int1(m_F1, m_F2, m_I1);
							break;
						case FuncType::Int2Float1:
							f_EventFuncInt2Float1(m_I1, m_I2, m_F1);
							break;
						case FuncType::Float2Int2:
							f_EventFuncFloat2Int2(m_F1, m_F2, m_I1, m_I2);
							break;
						case FuncType::Int1Float1:
							f_EventFuncInt1Float1(m_I1, m_F1);
							break;
						}

						DestroySelf();
					}	

					void DestroySelf()
					{
						n2dRemoveDeleteable(m_ID);

						CleanUpdaters();

						TimelineEvent::DestroySelf();

						SetDeleted(true);
					}

				};
			}
		}
	}
}