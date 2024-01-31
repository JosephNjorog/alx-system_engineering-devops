Let's break down the tasks in Networking Basics #1 project in detail as how i have done it:

1. **0. Change your home IP**:
   - **Task**: Write a Bash script to configure an Ubuntu server so that localhost resolves to `127.0.0.2` and `facebook.com` resolves to `8.8.8.8`.
   - **Approach**: Use the `/etc/hosts` file to map hostnames to IP addresses.
   - **Script**: Create a Bash script (`0-change_your_home_IP`) that modifies the `/etc/hosts` file accordingly.
   - **Testing**: Verify the changes by pinging `localhost` and `facebook.com` before and after running the script.

2. **1. Show attached IPs**:
   - **Task**: Write a Bash script to display all active IPv4 IPs on the machine.
   - **Approach**: Utilize the `ifconfig` command to fetch network interface information and extract IPv4 addresses.
   - **Script**: Develop a Bash script (`1-show_attached_IPs`) that parses the output of `ifconfig` to extract IPv4 addresses.
   - **Testing**: Execute the script and verify that it accurately displays active IPv4 addresses.

3. **2. Port listening on localhost** (Advanced):
   - **Task**: Write a Bash script that listens on port 98 on localhost.
   - **Approach**: Use `netcat` (nc) to listen on a specified port for incoming connections.
   - **Script**: Develop a Bash script (`100-port_listening_on_localhost`) that listens on port 98 using `netcat`.
   - **Testing**: Test the script by connecting to localhost on port 98 using `telnet` from another terminal, and verify that the script receives the transmitted text.

These tasks will deepen your understanding of networking fundamentals, including IP address resolution, network interface configuration, and socket communication. Ensure to follow the requirements and test thoroughly to validate the functionality of your scripts.
