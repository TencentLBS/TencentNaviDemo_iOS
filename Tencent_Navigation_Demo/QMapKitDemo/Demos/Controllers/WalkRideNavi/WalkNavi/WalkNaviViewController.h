//
//  WalkNaviViewController.h
//  QMapKitDemo
//
//  Created by ikaros on 2020/8/12.
//  Copyright © 2020 tencent. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <TNKNavigationKit/TNKNavigationKit.h>
#import <TNKNavigationKit/TNKLocationEntryProtocol.h>
#import <QMapKit/QMapKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface WalkNaviViewController : UIViewController<TNKWalkNaviDelegate, TNKWalkNaviViewDelegate,QMapViewDelegate>

@end

NS_ASSUME_NONNULL_END
