0x1B-Web_stack_debbuging_4
This is the 5th web stack debbuging project among the webstack debugging series

In this project i am provided a broken webstack in an isolated container, and tasked to fix them.

I used Puppet to automate the fixing of the webstack to a working state.

Tasks:page_with_curl:
0. Sky is the limit, let's bring that limit higher

0-the_sky_is_the_limit_not.pp: Puppet manifest that increases the amount of traffic an Apache web server can handle effectively.
1. User limit

1-user_limit.pp: Puppet manifest that modifies the operating system configuration so that it is possible to login with the username holberton and open a file without encountering any error.