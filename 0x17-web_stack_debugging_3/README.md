# Web stack debugging #3

![stagesofdebugging](https://github.com/Obony/alx-system_engineering-devops/assets/117737538/3fbf965b-7a78-4606-8881-f684f17f4341)

This is a project with broken/bugged webstacks in isolated containers,
and tasked with fixing the web stack to a working state by writing a script automating the commands necessary to fix the
web stack.

## Tasks :page_with_curl:

* **0. Strace is your friend**
  * [0-strace_is_your_friend.pp](./0-strace_is_your_friend.pp): Puppet manifest
  that fixes a typo error causing a WordPress application being served by an Apache
  web server to fail.
  * Usage: `puppet apply 0-strace_is_your_friend.pp`
