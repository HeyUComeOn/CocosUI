#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void TouchEvent(cocos2d::Ref*pSender ,cocos2d::ui::TouchEventType type);

	void selectedEvent(cocos2d::Ref* pSender,cocos2d::ui::CheckBox::EventType type);

	void sliderEvent(cocos2d::Ref *pSender, cocos2d::ui::Slider::EventType type);

	void update(float delta);

	void textFieldEvent(cocos2d::Ref *pSender, cocos2d::ui::TextField::EventType type);

	void pageViewEvent(cocos2d::Ref *pSender, cocos2d::ui::PageView::EventType type);
private:
	cocos2d::Label* _displayValueLabel;
	cocos2d::Label* _displayValueLabel2;
	int _count ;
	std::vector<std::string> _array;
	cocos2d::ui::RichText* _richText;
};

#endif // __HELLOWORLD_SCENE_H__
