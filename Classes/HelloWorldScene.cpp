#include "HelloWorldScene.h"
//#include "extensions/cocos-ext.h"


USING_NS_CC;
using namespace ui;
Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
		origin.y + closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = LabelTTF::create("Hello World", "Arial", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	/*
	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);*/

	//创建button
	Button*bt = Button::create("animationbuttonnormal.png",
		"animationbuttonpressed.png");
	bt->setTitleText("Test Button");
	bt->addTouchEventListener(this, toucheventselector(HelloWorld::TouchEvent));
	bt->setPosition(Vec2(visibleSize.width/2 ,visibleSize.height/2));
	addChild(bt);

	//checkBox
	CheckBox* checkBox = CheckBox::create("check_box_normal.png",
		"check_box_normal_press.png",
		"check_box_active.png",
		"check_box_normal_disable.png",
		"check_box_active_disable.png");
	checkBox->setPosition(Vec2(240, 240));

	checkBox->addEventListener(CC_CALLBACK_2(HelloWorld::selectedEvent, this));
	addChild(checkBox);

	// Create the slider
	_displayValueLabel = Label::createWithTTF("","fonts/Marker Felt.ttf",40);
	_displayValueLabel->setPosition(Vec2(220,300));
	addChild(_displayValueLabel);
	_displayValueLabel2 = Label::createWithTTF("","fonts/Marker Felt.ttf",40);
	_displayValueLabel2->setPosition(Vec2(600,300));
	addChild(_displayValueLabel2);
	Slider* slider = Slider::create();
	slider->loadBarTexture("sliderTrack.png");
	slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");
	slider->loadProgressBarTexture("sliderProgress.png");
	slider->setPosition(Vec2(200,280));
	slider->addEventListener(CC_CALLBACK_2(HelloWorld::sliderEvent, this));
	addChild(slider);

	// Create the imageview
	ImageView* imageView = ImageView::create("buttonHighlighted.png");
	imageView->setScale9Enabled(true);
	imageView->setContentSize(Size(300, 115));
	imageView->setPosition(Vec2(200, 320));
	addChild(imageView); 

	// Create the loading bar
	LoadingBar* loadingBar = LoadingBar::create("sliderProgress2.png",0.0f);
	loadingBar->setTag(0);
	//loadingBar->setScale9Enabled(true);
	//loadingBar->setCapInsets(Rect(0,0,0,0));
	//loadingBar->setContentSize(Size(3,1));
	loadingBar->setVisible(true);
	loadingBar->setDirection(LoadingBar::Direction::RIGHT);
	loadingBar->setPosition(Vec2(200, 440));
	_count = 0;
	this->schedule(schedule_selector(HelloWorld::update, this),0.01f);
	addChild(loadingBar,3);

	// Create the text atlas
	TextAtlas* textAtlas = TextAtlas::create("1234567890", "cocosui/labelatlas.png", 17, 22, "0");
	textAtlas->setPosition(Vec2(200, 480));
	addChild(textAtlas);  

	// Create the text
	Text* text2 = Text::create("Text2", "AmericanTypewriter", 30);
	text2->setPosition(Vec2(200,500));
	addChild(text2);

	Text* text3 = Text::create("Text3: Test the auto Enter", "AmericanTypewriter", 30);
	text3->setPosition(Vec2(400,200));
	text3->setContentSize(Size(300,300));
	text3->ignoreContentAdaptWithSize(false);
	text3->setTextHorizontalAlignment(TextHAlignment::LEFT);

	addChild(text3);

	// Create the TextBMFont
	TextBMFont* textBMFont = TextBMFont::create("BMFont", "bitmapFontTest2.fnt");
	textBMFont->setPosition(Vec2(400,230));
	addChild(textBMFont);

	// Create the textfield 可输入文字的文本框
	TextField* textField = TextField::create("input words here","fonts/Marker Felt.ttf",30);

	textField->setPosition(Vec2(400,270));
	textField->addEventListener(CC_CALLBACK_2(HelloWorld::textFieldEvent, this));
	textField->setMaxLengthEnabled(true);
	textField->setMaxLength(3);
	textField->setPasswordEnabled(true);
	textField->setPasswordStyleText("*");
	addChild(textField);

	// Create the layout
	Layout* layout = Layout::create();
	layout->setLayoutType(LAYOUT_LINEAR_VERTICAL);
	layout->setContentSize(Size(280, 150));
	layout->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
	layout->setBackGroundColor(Color3B::GREEN);
	Size backgroundSize = Director::getInstance()->getWinSize();
	layout->setPosition(Vec2(backgroundSize.width  / 2+100,
		backgroundSize.height  / 2));
	addChild(layout,5);

	Button* button = Button::create("animationbuttonnormal.png", "animationbuttonpressed.png");
	/*button->setPosition(Vec2(button->getContentSize().width / 2.0f,
		layout->getContentSize().height - button->getContentSize().height / 2.0f));*/

	LinearLayoutParameter* lp1 = LinearLayoutParameter::create();
	button->setLayoutParameter(lp1);
	lp1->setGravity(LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
	lp1->setMargin(Margin(0.0f, 5.0f, 0.0f, 10.0f));

	layout->addChild(button);

	Button* titleButton = Button::create("backtotopnormal.png", "backtotoppressed.png");
	titleButton->setTitleText("Title Button");
	//titleButton->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
	
	LinearLayoutParameter* lp2 = LinearLayoutParameter::create();
	titleButton->setLayoutParameter(lp2);
	lp2->setGravity(LinearLayoutParameter::LinearGravity::LEFT);
	lp2->setMargin(Margin(0.0f, 10.0f, 0.0f, 10.0f));

	layout->addChild(titleButton);

	Button* button_scale9 = Button::create("button.png", "buttonHighlighted.png");
	button_scale9->setScale9Enabled(true);
	button_scale9->setContentSize(Size(100.0f, button_scale9->getVirtualRendererSize().height));
	/*button_scale9->setPosition(Vec2(layout->getContentSize().width - button_scale9->getContentSize().width / 2.0f,
		button_scale9->getContentSize().height / 2.0f));*/
	
	LinearLayoutParameter* lp3 = LinearLayoutParameter::create();
	button_scale9->setLayoutParameter(lp3);
	lp3->setGravity(LinearLayoutParameter::LinearGravity::CENTER_HORIZONTAL);
	lp3->setMargin(Margin(0.0f, 10.0f, 0.0f, 10.0f));
	
	layout->addChild(button_scale9);

	// Create the scrollview by vertical
	ui::ScrollView* scrollView = ui::ScrollView::create();
	scrollView->setBounceEnabled(true);
	scrollView->setBackGroundImageScale9Enabled(true);
	scrollView->setBackGroundImage("green_edit.png");
	scrollView->setContentSize(Size(280.0f, 150.0f));
	scrollView->setPosition(Vec2(600,100));
	addChild(scrollView);

	ImageView* imageView3 = ImageView::create("ccicon.png");
	float innerWidth = scrollView->getContentSize().width;
	float innerHeight = scrollView->getContentSize().height + imageView3->getContentSize().height;
	imageView3->setPosition(Vec2(innerWidth / 2.0f, imageView3->getContentSize().height / 2.0f));
	scrollView->addChild(imageView3);   

	scrollView->setInnerContainerSize(Size(innerWidth, innerHeight));                

	Button* button5 = Button::create("animationbuttonnormal.png", "animationbuttonpressed.png");
	button5->setPosition(Vec2(innerWidth / 2.0f, scrollView->getInnerContainerSize().height - button5->getContentSize().height / 2.0f));
	scrollView->addChild(button5);

	Button* titleButton5 = Button::create("backtotopnormal.png", "backtotoppressed.png");
	titleButton5->setTitleText("Title Button");
	titleButton5->setPosition(Vec2(innerWidth / 2.0f, button5->getBottomBoundary() - button5->getContentSize().height));
	scrollView->addChild(titleButton5);

	Button* button_scale92 = Button::create("button.png", "buttonHighlighted.png");
	button_scale92->setScale9Enabled(true);
	button_scale92->setContentSize(Size(100.0f, button_scale92->getVirtualRendererSize().height));
	button_scale92->setPosition(Vec2(innerWidth / 2.0f, titleButton5->getBottomBoundary() - titleButton5->getContentSize().height));
	scrollView->addChild(button_scale92);

	// Create the dragpanel
	ui::ScrollView* scrollView2 = ui::ScrollView::create();
	scrollView2->setDirection(ui::ScrollView::Direction::BOTH);
	scrollView2->setTouchEnabled(true);
	scrollView2->setBounceEnabled(true);
	scrollView2->setBackGroundImageScale9Enabled(true);
	scrollView2->setBackGroundImage("green_edit.png");
	scrollView2->setContentSize(Size(210, 122.5));
	
	scrollView2->setPosition(Vec2(50,50));
	ImageView* imageView5 = ImageView::create("HelloWorld.png");
	scrollView2->addChild(imageView5);

	scrollView2->setInnerContainerSize(imageView5->getContentSize());
	Size innerSize = scrollView2->getInnerContainerSize();
	imageView5->setPosition(Vec2(innerSize.width / 2.0f, innerSize.height / 2.0f));
	//滚动到一个位置，最后一个参数表示速度是否衰减
	scrollView2->scrollToPercentBothDirection(Vec2(60,60),2.0f,true);
	addChild(scrollView2);

	// Create the page view
	PageView* pageView = PageView::create();
	pageView->setContentSize(Size(240.0f, 130.0f));
	pageView->setPosition(Vec2(300,0));

	pageView->removeAllPages();

	int pageCount = 4;
	for (int i = 0; i < pageCount; ++i)
	{
		Layout* layout = Layout::create();
		layout->setContentSize(Size(240.0f, 130.0f));

		ImageView* imageView = ImageView::create("scrollviewbg.png");
		imageView->setScale9Enabled(true);
		imageView->setContentSize(Size(240, 130));
		imageView->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
		layout->addChild(imageView);

		Text* label = Text::create(StringUtils::format("page %d",(i+1)), "fonts/Marker Felt.ttf", 30);
		label->setColor(Color3B(192, 192, 192));
		label->setPosition(Vec2(layout->getContentSize().width / 2.0f, layout->getContentSize().height / 2.0f));
		layout->addChild(label);

		pageView->insertPage(layout,i);
	}

	pageView->removePageAtIndex(0);
	pageView->scrollToPage(pageCount-2);

	pageView->addEventListener(CC_CALLBACK_2(HelloWorld::pageViewEvent, this));

	addChild(pageView);

	// create list view ex data

	for (int i = 0; i < 20; ++i)
	{
		std::string ccstr = StringUtils::format("listview_item_%d", i);
		_array.push_back(ccstr);
	}
	// Create the list view ex
	ListView* listView = ListView::create();
	// set list view ex direction
	listView->setDirection(ui::ScrollView::Direction::VERTICAL);
	listView->setBounceEnabled(true);
	listView->setBackGroundImage("green_edit.png");
	listView->setBackGroundImageScale9Enabled(true);
	listView->setContentSize(Size(240, 130));
	listView->setPosition(Vec2(400, 480));
	//listView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(UIListViewTest_Vertical::selectedItemEvent, this));
	//listView->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(UIListViewTest_Vertical::selectedItemEventScrollView,this));

	addChild(listView);


	// create model
	Button* default_button = Button::create("backtotoppressed.png", "backtotopnormal.png");
	default_button->setName("Title Button");

	Layout* default_item = Layout::create();
	default_item->setTouchEnabled(true);
	default_item->setContentSize(default_button->getContentSize());
	default_button->setPosition(Vec2(default_item->getContentSize().width / 2.0f,
		default_item->getContentSize().height / 2.0f));
	default_item->addChild(default_button);

	// set model
	listView->setItemModel(default_item);

	// add default item
	ssize_t count = _array.size();
	for (int i = 0; i < count / 4; ++i)
	{
		listView->pushBackDefaultItem();
	}
	// insert default item
	for (int i = 0; i < count / 4; ++i)
	{
		listView->insertDefaultItem(0);
	}

	listView->removeAllChildren();

	Sprite* testSprite = Sprite::create("backtotoppressed.png");
	testSprite->setPosition(Vec2(200,200));
	listView->addChild(testSprite);

	// add custom item
	for (int i = 0; i < count / 4; ++i)
	{
		Button* custom_button = Button::create("button.png", "buttonHighlighted.png");
		custom_button->setName("Title Button");
		custom_button->setScale9Enabled(true);
		custom_button->setContentSize(default_button->getContentSize());

		Layout *custom_item = Layout::create();
		custom_item->setContentSize(custom_button->getContentSize());
		custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));
		custom_item->addChild(custom_button);

		listView->addChild(custom_item);
	}
	// insert custom item
	Vector<Widget*>& items = listView->getItems();
	ssize_t items_count = items.size();
	for (int i = 0; i < count / 4; ++i)
	{
		Button* custom_button = Button::create("button.png", "buttonHighlighted.png");
		custom_button->setName("Title Button");
		custom_button->setScale9Enabled(true);
		custom_button->setContentSize(default_button->getContentSize());

		Layout *custom_item = Layout::create();
		custom_item->setContentSize(custom_button->getContentSize());
		custom_button->setPosition(Vec2(custom_item->getContentSize().width / 2.0f, custom_item->getContentSize().height / 2.0f));
		custom_item->addChild(custom_button);
		custom_item->setTag(1);

		listView->insertCustomItem(custom_item, items_count);
	}

	// set item data
	items_count = items.size();
	for (int i = 0; i < items_count; ++i)
	{
		Widget* item = listView->getItem(i);
		Button* button = static_cast<Button*>(item->getChildByName("Title Button"));
		ssize_t index = listView->getIndex(item);
		button->setTitleText(_array[index]);
	}

	// remove last item
	listView->removeChildByTag(1);

	// remove item by index
	items_count = items.size();
	listView->removeItem(items_count - 1);

	// set all items layout gravity
	listView->setGravity(ListView::Gravity::CENTER_VERTICAL);

	// set items margin
	listView->setItemsMargin(2.0f);

	// RichText
	_richText = RichText::create();
	_richText->ignoreContentAdaptWithSize(false);
	_richText->setContentSize(Size(100, 100));

	RichElementText* re1 = RichElementText::create(1, Color3B::WHITE, 255, "中国中国中国中国中国中国中国中国中国中国", "Marker Felt", 10);
	RichElementText* re2 = RichElementText::create(2, Color3B::YELLOW, 255, "And this is yellow. ", "Helvetica", 10);
	RichElementText* re3 = RichElementText::create(3, Color3B::BLUE, 255, "ご静聴ありがとうございました！！ご静聴ありがとうございました！！", "Helvetica", 10);
	RichElementText* re4 = RichElementText::create(4, Color3B::GREEN, 255, "And green. ", "Helvetica", 10);
	RichElementText* re5 = RichElementText::create(5, Color3B::RED, 255, "Last one is red ", "Helvetica", 10);

	RichElementImage* reimg = RichElementImage::create(6, Color3B::WHITE, 255, "sliderballnormal.png");

	cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfo("100/100.ExportJson");
	cocostudio::Armature *pAr = cocostudio::Armature::create("100");
	pAr->getAnimation()->play("Animation1");

	RichElementCustomNode* recustom = RichElementCustomNode::create(1, Color3B::WHITE, 255, pAr);
	RichElementText* re6 = RichElementText::create(7, Color3B::ORANGE, 255, "Have fun!! ", "Helvetica", 10);
	_richText->pushBackElement(re1);
	_richText->insertElement(re2, 1);
	_richText->pushBackElement(re3);
	_richText->pushBackElement(re4);
	_richText->pushBackElement(re5);
	_richText->insertElement(reimg, 2);
	_richText->pushBackElement(recustom);
	_richText->pushBackElement(re6);

	_richText->setPosition(Vec2(750, 550));
	_richText->setLocalZOrder(10);


	this->addChild(_richText);
	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::TouchEvent(Ref*pSender ,TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
		log("Touch Began");
		break;
	case Widget::TouchEventType::MOVED:
		log("Touch Moved");
		break;
	case Widget::TouchEventType::ENDED:
		log("Touch Ended");
		break;
	case Widget::TouchEventType::CANCELED:
		log("Touch Canceled");
		break;
	default:
		break;
	}
}

void HelloWorld::selectedEvent(Ref* pSender,CheckBox::EventType type)
{
	switch (type)
	{
	case CheckBox::EventType::SELECTED:
		log(String::createWithFormat("Selected")->getCString());
		break;

	case CheckBox::EventType::UNSELECTED:
		log(String::createWithFormat("Unselected")->getCString());
		break;

	default:
		break;
	}

}

void HelloWorld::sliderEvent(Ref *pSender, Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(pSender);
		int percent = slider->getPercent();
		_displayValueLabel->setString(String::createWithFormat("Percent %d", percent)->getCString());
	}
}

void HelloWorld::update(float delta)
{
	_count++;
	if (_count > 100)
	{
		_count = 0;
	}
	LoadingBar* loadingBar = static_cast<LoadingBar*>(this->getChildByTag(0));
	loadingBar->setPercent(_count);
}

void HelloWorld::textFieldEvent(Ref *pSender, TextField::EventType type)
{
	switch (type)
	{
	case TextField::EventType::ATTACH_WITH_IME:
		{
			TextField* textField = dynamic_cast<TextField*>(pSender);
			Size screenSize = CCDirector::getInstance()->getWinSize();
			textField->runAction(CCMoveTo::create(0.225f,
				Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f + textField->getContentSize().height / 2.0f)));
			_displayValueLabel2->setString(String::createWithFormat("attach with IME")->getCString());
		}
		break;

	case TextField::EventType::DETACH_WITH_IME:
		{
			TextField* textField = dynamic_cast<TextField*>(pSender);
			Size screenSize = CCDirector::getInstance()->getWinSize();
			textField->runAction(CCMoveTo::create(0.175f, Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f)));
			_displayValueLabel2->setString(String::createWithFormat("detach with IME")->getCString());
		}
		break;

	case TextField::EventType::INSERT_TEXT:
		_displayValueLabel2->setString(String::createWithFormat("insert words")->getCString());
		break;

	case TextField::EventType::DELETE_BACKWARD:
		_displayValueLabel2->setString(String::createWithFormat("delete word")->getCString());
		break;

	default:
		break;
	}
}


void HelloWorld::pageViewEvent(Ref *pSender, PageView::EventType type)
{
	switch (type)
	{
	case PageView::EventType::TURNING:
		{
			PageView* pageView = dynamic_cast<PageView*>(pSender);

			log(CCString::createWithFormat("page = %ld", pageView->getCurPageIndex() + 1)->getCString());
		}
		break;

	default:
		break;
	}
}
