# ToolWeb

ToolWeb is a command-line tool designed to automate the use of several web penetration testing tools. It allows you to run tools such as `nmap`, `nikto`, `gobuster`, and `wpscan` on a target IP address.

## Features

- **Help Option (`-h`)**: Displays usage instructions.
- **Target IP (`-ip <IP>`)**: Specifies the target IP address for the penetration testing tools.
- **Nmap (`-nmap`)**: Runs a full scan on the specified target IP using Nmap.
- **Nikto (`-nikto`)**: Runs a security scan on the target IP using Nikto.
- **GoBuster (`-gobuster`)**: Performs directory and file enumeration on the target website using GoBuster.
- **WPScan (`-wpscan`)**: Scans WordPress websites for security issues using WPScan.

## Installation

Before using ToolWeb, you may need to install some dependencies like Nmap, Nikto, GoBuster, and WPScan. If any of these tools are missing, ToolWeb will prompt you to install them based on your Linux distribution (Ubuntu, Fedora, Arch, etc.).

The tool automatically detects your Linux distribution and installs the required tools.

## Usage

### Basic Syntax
```bash
./ToolWeb [OPTIONS]
```

### Options:
- `-h`: Displays this help message.
- `-ip <IP>`: Specifies the target IP address.
- `-nmap`: Runs Nmap on the specified target IP.
- `-nikto`: Runs Nikto on the specified target IP.
- `-gobuster`: Runs GoBuster on the specified target IP.
- `-wpscan`: Runs WPScan on the specified target IP.

### Example:
```bash
./ToolWeb -ip 127.0.0.1 -nmap
```

This example runs Nmap on the target IP `127.0.0.1`.

## Contributing

Contributions are welcome! Feel free to fork the repository, make changes, and submit pull requests. If you have any improvements, bug fixes, or suggestions, don't hesitate to contribute to this project.

## License

This project is licensed under the MIT License - see the [LICENSE](license.md) file for details.

