//
//  HomeViewController.m
//  iHome
//
//  Created by Piotr Giedziun on 11/11/13.
//  Copyright (c) 2013 Piotr Giedziun. All rights reserved.
//
#import "MBProgressHUD.h"
#import "HomeViewController.h"
#import "statics.h"

@interface HomeViewController ()

@end

@implementation HomeViewController


- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)request: (NSString *)url
{
    NSURL *myURL = [NSURL URLWithString:[NSString stringWithFormat:@"%@%@", API_URL, url]];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:myURL
                                                           cachePolicy:NSURLRequestReloadIgnoringLocalCacheData timeoutInterval:60];
    
    [[NSURLConnection alloc] initWithRequest:request delegate:self];
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response
{
    responseData = [[NSMutableData alloc] init];
}

- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
    [responseData appendData:data];
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error
{
    [self hideProgressBar];
    UIAlertView *errorAlert = [[UIAlertView alloc]
                                        initWithTitle:@"Error" message:@"Request timeout" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
    [errorAlert show];
}
                
- (void)connectionDidFinishLoading:(NSURLConnection *)connection
{
    [self hideProgressBar];
    NSLog(@"Succeeded! Received %d bytes of data",[responseData length]);
    
    NSString *txt = [[NSString alloc] initWithData:responseData encoding: NSASCIIStringEncoding];
    UISwitch *switchStatus = (UIButton *)[self.view viewWithTag:1];
    if ([txt isEqualToString:@"on"]) {
        switchStatus.on = TRUE;
    }

}


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // load default state
    [self showProgressBar];
    [self request:@"status/get"];
}

- (IBAction) toggleSwitch: (id) sender {
    UISwitch *onoff = (UISwitch *) sender;
    if ( onoff.tag != 1) {
        [sender setOn:NO animated:YES];
        UIAlertView *notImplementedAlert = [[UIAlertView alloc]
                                   initWithTitle:@"Error" message:@"Not implemented yet!" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
        [notImplementedAlert show];
    }else{
        [self showProgressBar];
        [self request:[NSString stringWithFormat:@"status/%@", onoff.on?@"on":@"off"]];
    }
}

- (void)showProgressBar
{
    hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    hud.labelText = @"Loading..";
    [hud show:YES];
}

- (void)hideProgressBar
{
    [hud hide:YES];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath
{
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

/*
#pragma mark - Navigation

// In a story board-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}

 */

@end
