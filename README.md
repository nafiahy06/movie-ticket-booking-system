Project Overview:
CiNSUHUB is a console-based movie ticket booking system built in C as a group project in our first semester of university. It handles login, booking management, file persistence, billing with discounts, and printed tickets, all through a terminal interface.
Features

Login authentication:
Add, view, search, edit, and delete bookings
Records auto-renumber after deletion to avoid gaps
Input validation for phone numbers and ticket counts
Bill generation with student and bulk booking discounts
Formatted ticket printout with a simulated QR code
All data saved to and loaded from a text file

My Contributions:
I was responsible for the core data management layer of the system — the parts that make the program reliable and persistent:

Save & Load (saveToFile / loadFromFile) — designed the file format and handled reading and writing all booking records to disk, including sequential renumbering on load to keep records clean after deletions

Delete (deleteBooking) — implemented deletion with confirmation, auto-renumbering of remaining records, and a display showing occupied and free slots

Edit (edit) — built the full edit flow including name search, menu-driven selection for movie, showtime, seat class, and ticket count to prevent typos, phone validation, and automatic total price recalculation

Login & Main Menu — took over these shared tasks when teammates were unavailable, keeping the project on track

Ticket Generator (generateTicket) — added independently as an original feature; prints a formatted ticket with a simulated QR block, something not in the original requirements

I also used AI (primarily Claude) to help debug, fix formatting issues, and improve input validation. The feature ideas, logic, and decisions of my tasks were mine — AI helped me implement them correctly as someone still learning C.

Teamwork:
Teammate 1 — View and Search functions
Teammate 2 — Add Booking and Bill Generation
Myself — Save/Load, Delete, Edit, Login, Main Menu, Ticket Generator

What I Learned
This was my first real programming project. Working in C taught me how memory, file I/O, and structs actually work at a low level. Managing a shared codebase with teammates also showed me how important clean structure and communication are, things I will carry into every project after this.