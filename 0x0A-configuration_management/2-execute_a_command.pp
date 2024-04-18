# Execute command
exec {'killmenow':
command => '/bin/pkill -f "killmenow"',
}
