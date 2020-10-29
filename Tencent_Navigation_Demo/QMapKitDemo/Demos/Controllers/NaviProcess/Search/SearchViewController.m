//
//  SearchViewController.m
//  NavigationDemo
//
//  Created by xue on 2018/1/15.
//  Copyright © 2018年 xue. All rights reserved.
//

#import "SearchViewController.h"
#import "SearchResultTableViewCell.h"
#import "SVProgressHUD.h"
#import "SearchManager.h"
#import "SearchRecordTableViewCell.h"
#import <UIKit/UIKit.h>
#import "MathTool.h"
#import "ReplaceUnicode.h"

@interface SearchViewController () <UITextFieldDelegate, QMSSearchDelegate, UITableViewDelegate, UITableViewDataSource,UISearchBarDelegate,UICollectionViewDelegate>

@property (nonatomic, strong) QMSSearcher *searcher;

@property (nonatomic, strong) UIView *topView;
@property (nonatomic, strong) UIView *bottomView;

@property (nonatomic, strong) NSMutableDictionary *dictHistory;
@property (nonatomic, strong) NSArray *resultArray;


@property (nonatomic, strong) NSArray *recordArray;
@property (nonatomic, strong) UITableView *resultTableView;
@property (nonatomic, strong) UISearchBar *customSearchBar;
@property (nonatomic, strong) UITextField *searchField;

@property (nonatomic, strong) UITableView *regionTableView;
@property (nonatomic, strong) NSMutableArray *regionArray;
@property (nonatomic, strong) UIButton *regionButton;
@property (nonatomic, copy) NSString *regionStr;

@property (nonatomic) BOOL isHistoryEmpty;

@end

@implementation SearchViewController

#pragma mark - life cycle
- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.isHistoryEmpty = YES;
    
    _regionStr = @"北京";
    
    [self setupSearcher];

    [self setupTopArea];
    
    [self setupBottomArea];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:NO];
    [self.navigationController setNavigationBarHidden:NO];
    [self.navigationController setToolbarHidden:YES animated:animated];
    self.navigationController.interactivePopGestureRecognizer.delegate = (id)self;
    
    [self readNSUserDefaults];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [self.searchField resignFirstResponder];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


#pragma mark - Setup

- (void)setupSearcher
{
    self.searcher = [[QMSSearcher alloc]init];
    self.searcher.delegate = self;
}

- (void)setupTopArea
{
    CGFloat width = self.view.frame.size.width;
    
    UIView *topView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, width, 44)];
    self.navigationItem.titleView = topView;
    
    _regionButton = [[UIButton alloc] initWithFrame:CGRectMake(0, 0, 50, 44)];
    _regionButton.selected = NO;
    [_regionButton setTitle:@"北京" forState:UIControlStateNormal];
    _regionButton.titleLabel.font = [UIFont systemFontOfSize:14];
//    _regionButton.titleEdgeInsets = UIEdgeInsetsMake(0, -16, 0, 16);
//    _regionButton.imageEdgeInsets = UIEdgeInsetsMake(0, 30, 0, -30);
    [_regionButton setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    [_regionButton setTitleColor:[UIColor blueColor] forState:UIControlStateSelected];
//    [_regionButton setImage:[UIImage imageNamed:@"open"] forState:UIControlStateNormal];
//    [_regionButton setImage:[UIImage imageNamed:@"close"] forState:UIControlStateSelected];
    [_regionButton addTarget:self action:@selector(handleRegionSelect:) forControlEvents:UIControlEventTouchUpInside];
    [topView addSubview:_regionButton];
    
    UIView *line = [[UIView alloc] initWithFrame:CGRectMake(50, 0, 0.5, 44)];
    line.backgroundColor = [UIColor lightGrayColor];
    [topView addSubview:line];
    
    self.searchField = [[UITextField alloc] initWithFrame:CGRectMake(50, 0, self.view.frame.size.width - 50, 44)];
    self.searchField.leftView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 10, 0)];
    self.searchField.leftViewMode = UITextFieldViewModeAlways;
    
    if(self.placeholderString)
    {
        self.searchField.placeholder = self.placeholderString;
    }
    else
    {
        self.searchField.placeholder = nil;
    }
    
    [self.searchField becomeFirstResponder];
    
    self.searchField.clearButtonMode = UITextFieldViewModeAlways;
    self.searchField.returnKeyType = UIReturnKeyDefault;
    self.searchField.delegate = self;
    [self.searchField addTarget:self action:@selector(textFieldDidChange:) forControlEvents:UIControlEventEditingChanged];
    [topView addSubview:self.searchField];
    
}

- (void)setupBottomArea
{

    CGFloat width  = self.view.frame.size.width;
    CGFloat height = self.view.frame.size.height;
    
    CGRect bottomAreaFrame = CGRectMake(0, kNavigationBarHeight , width, height-64);
    self.bottomView = [[UIView alloc] initWithFrame:bottomAreaFrame];
    self.bottomView.backgroundColor = [UIColor whiteColor];
    
    [self.view addSubview:self.bottomView];
    
    self.resultTableView = [[UITableView alloc] initWithFrame:CGRectMake(0, 0, width, bottomAreaFrame.size.height ) style:UITableViewStylePlain];
    
    self.resultTableView.delegate = self;
    self.resultTableView.dataSource = self;
    
    self.resultTableView.tableFooterView = [[UIView alloc] init];
    self.resultTableView.separatorInset = UIEdgeInsetsZero;
    
    [self.bottomView addSubview:self.resultTableView];
    
}

#pragma mark - actions

- (void)cancelSearch
{
    [self.navigationController popViewControllerAnimated:YES];
}

- (void)textFieldDidChange:(UITextField *)textField
{
//    NSLog(@"textfield: %@", textField.text);
    
    if (textField.text.length != 0)
    {
        self.isHistoryEmpty = NO;
        [self searchResultWithString:textField.text];
    }
    else
    {
        self.isHistoryEmpty = YES;
        [self showResultWithArray:self.recordArray];
        
    }
    
}


- (void)searchResultWithString:(NSString*)string
{
    QMSSuggestionSearchOption *sugSearchOption = [[QMSSuggestionSearchOption alloc]init];

    [sugSearchOption setKeyword:string];
    
    // 设置此参数会限制检索城市
    [sugSearchOption setRegion:_regionStr];
    [self.searcher searchWithSuggestionSearchOption:sugSearchOption];
    
    [SVProgressHUD show];
}

// 　显示点击搜索栏之后的result， 形成array
- (void)showResultWithArray:(NSArray*)result
{
    //self.resultTableView.hidden = (!result)? YES : NO;
    
    if (self.isHistoryEmpty == NO) {
        self.resultArray = result;
    }else{
        self.recordArray = result;
    }
    
    [self.resultTableView reloadData];
}

/**
 * 区域按钮点击事件
 */
- (void)handleRegionSelect:(UIButton *)button
{
    button.selected = !button.selected;
    
    if (button.isSelected)
    {
        [self setRegionViewHidden:NO];
    }
    else
    {
        [self setRegionViewHidden:YES];
    }
}

- (void)setRegionViewHidden:(BOOL)isHidden
{
    _regionTableView.hidden = isHidden;
    _resultTableView.hidden = !isHidden;
}


- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer
{
    return YES ;
}


#pragma mark - textField delegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    [textField resignFirstResponder];
    return YES;
}

- (BOOL)textFieldShouldClear:(UITextField *)textField
{
    [self showResultWithArray:nil];
    return YES;
}

- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [self.searchField resignFirstResponder];
    
}

- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView
{
    [self.searchField resignFirstResponder];
}

#pragma mark - search delegate
// 查询字的补充与回调接口
- (void)searchWithSuggestionSearchOption:(QMSSuggestionSearchOption *)
suggestionSearchOption didReceiveResult:(QMSSuggestionResult *)suggestionSearchResult
{
    
    [SVProgressHUD dismiss];
    
    NSArray *result = suggestionSearchResult.dataArray;
    
    [self showResultWithArray:result];
}

// 查询出现错误
- (void)searchWithSearchOption:(QMSSearchOption *)searchOption didFailWithError:(NSError*)error
{
    [SVProgressHUD dismiss];
    
    if([self.delegate respondsToSelector:@selector(searchViewController:didFailSearchWithError:)])
    {
        [self.delegate searchViewController:self didFailSearchWithError:error];
    }
}

#pragma mark - tableView delegate
// UITableViewDataSource里面有两个required numberOfRowsInSection， cellForRowAtIndexPath
- (NSInteger)tableView:(nonnull UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if (tableView == self.regionTableView)
    {
        return self.regionArray.count;
    }
    else
    {
        if (self.isHistoryEmpty == YES)
        {
            return self.searchHistories.count;
        }
        else
        {
            return self.resultArray.count;
        }
    }
}
// 每一个搜索结果的列表的高度 UITableViewDelegate里面的optional
- (CGFloat)tableView:(nonnull UITableView *)tableView heightForRowAtIndexPath:(nonnull NSIndexPath *)indexPath
{
    if (tableView == self.regionTableView)
    {
        return 44;
    }
    else
    {
         return 70;
    }
}

// 显示那些suggestion的结果
- (UITableViewCell *)tableView:(nonnull UITableView *)tableView cellForRowAtIndexPath:(nonnull NSIndexPath *)indexPath
{
    if (tableView == self.regionTableView)
    {
        NSString *cellID = @"regionCell";
        
        UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellID];
        if (!cell)
        {
            cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellID];
        }
        cell.textLabel.text = self.regionArray[indexPath.row];
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
        return cell;
    }
    else
    {
        if (self.isHistoryEmpty == YES)
        {
            static NSString *searchRecordCell = @"searchRecordCell";
            SearchRecordTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:searchRecordCell];
            if (cell == nil)
            {
                cell = [[SearchRecordTableViewCell alloc]initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:searchRecordCell];
            }
            
            if (self.searchHistories.count != 0)
            {
                QMSSuggestionPoiData* data = [[QMSSuggestionPoiData alloc] init];
                data.title = [self.searchHistories[self.searchHistories.count - 1 - indexPath.row] objectForKey:@"hisTitle"];
                data.address = [self.searchHistories[self.searchHistories.count - 1 - indexPath.row] objectForKey:@"hisAddress"];
                data.id_ = [self.searchHistories[self.searchHistories.count - 1 - indexPath.row] objectForKey:@"hisId"];
                CLLocationDegrees dataLongitude = [[self.searchHistories[self.searchHistories.count - 1 - indexPath.row] objectForKey:@"hisLongitude"] doubleValue];
                CLLocationDegrees dataLatitude = [[self.searchHistories[self.searchHistories.count - 1 - indexPath.row] objectForKey:@"hisLatitude"] doubleValue];
                
                data.location = CLLocationCoordinate2DMake(dataLatitude, dataLongitude);
                
                cell.iconImageView.image = [UIImage imageNamed:@"history"];
                cell.titleLabel.text     = data.title;
                cell.addressLabel.text   = data.address;
                cell.distanceLabel.text  = [self distanceWithLocation:data.location];
            }
            
            self.recordArray = [self.searchHistories mutableCopy];
            
            self.placeholderString = self.recordArray[self.recordArray.count - 1];
            return cell;
            
        }
        else
        {
            static NSString *cellID = @"resultTableViewCell";
            SearchResultTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellID];
            if (cell == nil)
            {
                cell = [[SearchResultTableViewCell alloc]initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:cellID];
            }
            QMSSuggestionPoiData* data = self.resultArray[indexPath.row];
            
            cell.iconImageView.image = [UIImage imageNamed:@"location.png"];
            cell.titleLabel.text     = data.title;
            cell.addressLabel.text   = data.address;
            cell.distanceLabel.text  = [self distanceWithLocation:data.location];
            return cell;
        }
    }
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (tableView == self.regionTableView)
    {
        [_regionButton setTitle:self.regionArray[indexPath.row] forState:UIControlStateNormal];
        _regionButton.selected = NO;
        [self setRegionViewHidden:YES];
        _regionStr = self.regionArray[indexPath.row];
        [_regionButton setTitle:_regionStr forState:UIControlStateNormal];
    }
    else
    {
        if (self.isHistoryEmpty == YES)
        {
            QMSSuggestionPoiData* data = [[QMSSuggestionPoiData alloc] init];
            data.title = [self.searchHistories[self.searchHistories.count - 1 - indexPath.row] objectForKey:@"hisTitle"];
//            data.address =  [self.searchHistories[self.searchHistories.count - 1 - indexPath.row] objectForKey:@"hisAddress"];
            data.id_ = [self.searchHistories[self.searchHistories.count - 1 - indexPath.row] objectForKey:@"hisId"];
            CLLocationDegrees dataLongitude = [[self.searchHistories[self.searchHistories.count - 1 - indexPath.row] objectForKey:@"hisLongitude"] doubleValue];
            CLLocationDegrees dataLatitude = [[self.searchHistories[self.searchHistories.count - 1 - indexPath.row] objectForKey:@"hisLatitude"] doubleValue];
            
            data.location = CLLocationCoordinate2DMake(dataLatitude, dataLongitude);
            
            if ([self.delegate respondsToSelector:@selector(searchViewController:didSuccessSearchWithData:)]) {
                
                [self.delegate searchViewController:self didSuccessSearchWithData:data];
            }
            
            [self.navigationController popViewControllerAnimated:YES];
            
        }
        else
        {
            QMSSuggestionPoiData *data = self.resultArray[indexPath.row];
            
            if([self.delegate respondsToSelector:@selector(searchViewController:didSuccessSearchWithData:)])
            {
                [self.delegate searchViewController:self didSuccessSearchWithData:data];
            }
            
            [self.navigationController popViewControllerAnimated:YES];
            
            NSString *str = [ReplaceUnicode replaceUnicode:data.title];
            NSString *address = [ReplaceUnicode replaceUnicode:data.address];
            NSString *destId = data.id_;
            NSString *destLocationLongitude = @(data.location.longitude).stringValue;
            NSString *destLocationLatitude = @(data.location.latitude).stringValue;
            
            self.dictHistory = [[NSMutableDictionary alloc] init];
            
            [self.dictHistory setObject:str forKey:@"hisTitle"];
            [self.dictHistory setObject:address forKey:@"hisAddress"];
            [self.dictHistory setObject:destId forKey:@"hisId"];
            [self.dictHistory setObject:destLocationLongitude forKey:@"hisLongitude"];
            [self.dictHistory setObject:destLocationLatitude forKey:@"hisLatitude"];
            
            
            [self.searchHistories addObject:self.dictHistory];
            
            [self saveNSUserDefaults];
            [self.dictHistory removeAllObjects];
            
        }
    }
}

- (NSString *)tableView:(UITableView *)tableView titleForDeleteConfirmationButtonForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return @"删除";
}

- (UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    //设置推荐结果不可编辑，历史结果可以编辑
    if (self.isHistoryEmpty == NO)
    {
        return UITableViewCellEditingStyleNone;
    }
    else
    {
        return UITableViewCellEditingStyleDelete;
    }
}

-(void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    
    if (editingStyle == UITableViewCellEditingStyleDelete)
    {
        if (indexPath.row < [self.searchHistories count])
        {
            //删除单个记录的时候，也要按照之前的排序
            [self.searchHistories removeObjectAtIndex:self.searchHistories.count-1-indexPath.row];
            
            [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationLeft];
            
            [self saveNSUserDefaults];
            
        }
    }
}

#pragma mark - tableViewDataSource


-(void)scrollViewDidScroll:(UIScrollView *)scrollView
{
    scrollView = self.resultTableView;
    [self.searchField resignFirstResponder];
}

// 删除历史记录
- (void)deleteBtnAction:(UIButton *)sender
{
    [SearchManager removeAllArray];
    [self.searchHistories removeAllObjects];
    [self.resultTableView reloadData];
}

// 保存历史记录
- (void)saveNSUserDefaults
{
    //把要传的数据通过nsarray传到userdefaults
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSMutableArray *removedSearchHistories = [[NSMutableArray alloc] init];
    removedSearchHistories = [self removeDuplicatedElement:self.searchHistories];
    
    NSArray *hisArray = [NSArray arrayWithArray:removedSearchHistories];
    
    [defaults setObject:hisArray forKey:@"myArray"];
    [defaults synchronize];
    [self.resultTableView reloadData];
}

// 取出缓存的数据
- (void)readNSUserDefaults
{
    
    NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
    // 读取nsarray类型的数据
    NSArray *myArray = [userDefaults arrayForKey:@"myArray"];
    // 把nsarray转化为nsmutablearray
    NSMutableArray *myMutableArray = [NSMutableArray arrayWithArray:myArray];
    self.searchHistories = myMutableArray;
    [self.resultTableView reloadData];
}


#pragma mark - tools
- (NSString *)distanceWithLocation:(CLLocationCoordinate2D)location
{
    CLLocation *startLocation;
    
    if([self.dataSource respondsToSelector:@selector(searchViewControllerStartLocationForSearchRequest:)])
    {
        startLocation = [self.dataSource searchViewControllerStartLocationForSearchRequest:self];
    }
    
    if(startLocation == nil) return @"";
    
    CLLocation* stopLocation = [[CLLocation alloc] initWithLatitude:location.latitude longitude:location.longitude];
    
    CLLocationDistance distance = [stopLocation distanceFromLocation:startLocation];
    
    return [NSString stringWithFormat:@"%.2f 公里",distance/1000];
}

- (NSMutableArray *)removeDuplicatedElement:(NSMutableArray *)originalArray
{
    if ([originalArray count] <= 1)
    {
        return originalArray;
    }
    

    NSMutableArray *resultArray = [[NSMutableArray alloc] init];
    
    for (int i = 0; i < originalArray.count; i++)
    {
        if ([resultArray containsObject: [originalArray objectAtIndex:i]] == NO)
        {
            [resultArray addObject:[originalArray objectAtIndex:i]];
        }
        else
        {
            [resultArray removeObject:[originalArray objectAtIndex:i]];
            [resultArray insertObject:[originalArray objectAtIndex:i] atIndex:resultArray.count];
        }
    }
    
    return resultArray;
}

#pragma mark - Lazy load
-(NSMutableArray *)regionArray
{
    if (!_regionArray)
    {
        _regionArray = [NSMutableArray array];
        [_regionArray addObjectsFromArray:@[@"北京",@"广州",@"天津",@"重庆"]];
    }
    return _regionArray;
}

-(UITableView *)regionTableView
{
    if (!_regionTableView)
    {
        _regionTableView = [[UITableView alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height) style: UITableViewStylePlain];
        _regionTableView.delegate = self;
        _regionTableView.dataSource = self;
        _regionTableView.tableFooterView = [UIView new];
        _regionTableView.hidden = YES;
        [_bottomView addSubview:_regionTableView];
    }
    return _regionTableView;
}


@end
