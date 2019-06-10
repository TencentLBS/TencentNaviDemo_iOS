//
//  EntryData.h
//  QMapKitDemoNew
//
//  Created by Tencent on 17/5/11.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Cell : NSObject

@property (nonatomic, copy) NSString *title;

@property (nonatomic, copy) NSString *controllerClassName;
@property (nonatomic, assign) BOOL disabled;

@end

@interface Section : NSObject

@property (nonatomic, copy) NSString *title;

@property (nonatomic, strong) NSMutableArray<Cell *> *cells;

@end

@interface EntryData : NSObject

@property (nonatomic, copy) NSString *title;

@property (nonatomic, strong) NSMutableArray<Section *> *sections;

+ (instancetype)constructDefaultEntryData;

@end
