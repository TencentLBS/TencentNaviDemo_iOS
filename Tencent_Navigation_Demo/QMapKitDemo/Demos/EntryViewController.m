//
//  EntryViewController.m
//  QMapKitDemoNew
//
//  Created by Tencent on 17/5/11.
//  Copyright © 2017年 Tencent. All rights reserved.
//

#import "EntryViewController.h"
#import "EntryData.h"
#import "BaseNaviViewController.h"
@interface EntryViewController () <UITableViewDelegate, UITableViewDataSource>

@property (nonatomic, strong) UITableView *tableView;

@property (nonatomic, strong) EntryData *entry;

@end

@implementation EntryViewController

#pragma mark - UITableViewDataDelegate

// Cell 点击回调.
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    Section *sectionData = self.entry.sections[indexPath.section];
    Cell *cellData = sectionData.cells[indexPath.row];
    
    // 该Demo 暂不支持.
    if (cellData.disabled) return;
    
    BaseNaviViewController *controller = [[NSClassFromString(cellData.controllerClassName) alloc] init];
    controller.edgesForExtendedLayout = UIRectEdgeBottom;
    
    controller.title = cellData.title;
    
    [self.navigationController pushViewController:controller animated:YES];
}

#pragma mark - UITableViewDataSource

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *cellIdentifier = @"cellIdentifier";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    if (cell == nil)
    {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:cellIdentifier];
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    }
    
    Section *sectionData = self.entry.sections[indexPath.section];
    Cell *cellData = sectionData.cells[indexPath.row];
    
    NSString *title                 = nil;
    UIColor *normalColor            = nil;
    UIColor *highlightedTextColor   = nil;
    UITableViewCellSelectionStyle   type;
    
    // 有效态.
    if (!cellData.disabled)
    {
        title                   = cellData.title;
        normalColor             = [UIColor blackColor];
        highlightedTextColor    = [UIColor whiteColor];
        type                    = UITableViewCellSelectionStyleBlue;
    }
    // 禁用态.
    else
    {
        title                   = [cellData.title stringByAppendingString:@" (Not Supported)"];
        normalColor             = [UIColor grayColor];
        highlightedTextColor    = [UIColor grayColor];
        type                    = UITableViewCellSelectionStyleNone;
    }
    
    // TextLabel.
    cell.textLabel.text                 = title;
    cell.textLabel.textColor            = normalColor;
    cell.textLabel.highlightedTextColor = highlightedTextColor;
    
    // DetailLabel.
    cell.detailTextLabel.text                 = cellData.controllerClassName;
    cell.detailTextLabel.textColor            = normalColor;
    cell.detailTextLabel.highlightedTextColor = highlightedTextColor;
    
    cell.selectionStyle = type;
    
    return cell;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    Section *sectionData = self.entry.sections[section];
    
    return sectionData.cells.count;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return self.entry.sections.count;
}

- (nullable NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section
{
    Section *sectionData = self.entry.sections[section];
    
    return sectionData.title;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 60;
}

#pragma mark - Setup

- (void)setupTableView
{
    self.tableView = [[UITableView alloc] initWithFrame:self.view.bounds style:UITableViewStyleGrouped];
    self.tableView.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth;
    self.tableView.delegate   = self;
    self.tableView.dataSource = self;
    
    [self.view addSubview:self.tableView];
}

#pragma mark - Life Cycle

- (instancetype)init
{
    if (self = [super init])
    {
        // 构建tableView 对应的数据结构.
        self.entry = [EntryData constructDefaultEntryData];
    }
    
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.title = self.entry.title;
    
    [self setupTableView];
}

@end
