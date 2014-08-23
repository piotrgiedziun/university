//
//  WebViewController.m
//  iHome
//
//  Created by Piotr Giedziun on 11/11/13.
//  Copyright (c) 2013 Piotr Giedziun. All rights reserved.
//
#import "WebViewController.h"
#import "MBProgressHUD.h"
#import "statics.h"

@interface WebViewController ()
    
@end

@implementation WebViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"%@info", API_URL]];
    NSURLRequest *requestObj = [NSURLRequest requestWithURL:url];
    _webView.delegate = (id)self;
    [_webView loadRequest:requestObj];
    
    UIRefreshControl *refreshControl = [[UIRefreshControl alloc] init];
    [refreshControl addTarget:self action:@selector(handleRefresh:) forControlEvents:UIControlEventValueChanged];
    [_webView.scrollView addSubview:refreshControl];
}

-(void)handleRefresh:(UIRefreshControl *)refresh {
    // Reload
    NSURL *url = [NSURL URLWithString:[NSString stringWithFormat:@"%@info", API_URL]];
    NSURLRequest *requestObj = [NSURLRequest requestWithURL:url];
    [_webView loadRequest:requestObj];
    [refresh endRefreshing];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
