;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; ;;;                 .emacs file for EZitor                 ;;;
;; ;;;---------------------------------------------------------;;;
;; ;;;             BO-KYUN NA   bkna@ecs.syr.edu              ;;;
;; ;;;             Computer and Information cience            ;;;
;; ;;;                  SYRACUSE NIVERSITY                    ;;; 
;;,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
;;    Currently, in KPU (bkna@kpu.ac.kr)                      ;;;
;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; 
;;
;; Warning!!!  Do "M-x byte-compile-file" then ".emacs" 
;;             or you will lose this file!
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;            Environmental setup 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Some macros.
(defmacro GNUEmacs (&rest x)
  (list 'if (string-match "GNU Emacs 20" (version)) (cons 'progn x)))
(defmacro XEmacs (&rest x)
  (list 'if (string-match "XEmacs 20" (version)) (cons 'progn x)))
(defmacro Xlaunch (&rest x)
  (list 'if (eq window-system 'x)(cons 'progn x)))

(GNUEmacs 
 (Xlaunch
     (define-key global-map [(delete)]    "\C-d") 
))

(XEmacs
 (if (eq window-system 'x)
     (global-set-key (read-kbd-macro "DEL") 'delete-char)
   (or (global-set-key "[3~" 'delete-char))
   ))

;;; Set up the keyboard so the delete key on both the regular keyboard
;;; and the keypad delete the character under the cursor and to the right
;;; under X, instead of the default, backspace behavior.
(global-set-key [delete] 'delete-char)
(global-set-key [kp-delete] 'delete-char)

;;; By default we starting in text mode.
(setq initial-major-mode
      (lambda ()
        (text-mode)
        (turn-on-auto-fill)
	(font-lock-mode)
	))

;;;  printing into a local printer
(setq lpr-switches '("-Pcristo"))

;(setq mh-lpr-command-format "lpr -Pps -h")
(setq mh-lpr-command-format "enscript -2rG -Pcristo -h")
(setq mh-ins-buf-prefix ">")
(put 'eval-expression 'disabled nil)

;;; Auto Indentation
(setq text-mode-hook 'turn-on-auto-fill)

;; Hiding ^M in DOS files
(defun dosify ()
  "Take a UNIX file and make it useful to DOS"
  (interactive)
  (goto-char (point-min))
  (while (not (eobp))
    (end-of-line)
    (insert "")
    (forward-char 1)))

(defun trim ()
  "Trim trailing whitespace from entire file"
  (interactive)
  (save-excursion
    (goto-char (point-min))
    (replace-regexp "[\r]+$" "")))


;; Macro
(global-set-key "\C-cl" 'goto-line)
(global-set-key "\C-cw" 'what-line)
(global-set-key "\C-cm" 'mh-rmail)
(local-set-key "\C-cr" 'replace-string)
(local-set-key "\C-ck" 'kill-rectangle)
(local-set-key "\C-cy" 'yank-rectangle)
(local-set-key "\C-cn" 'name-last-kbd-macro)
(local-set-key "\C-ci" 'insert-kbd-macro)
(local-set-key "\C-cs" 'ispell-buffer)
;;; Use `kbd' instead of `read-kbd-macro' if using GNU Emacs 20 or better. 
;(global-set-key (read-kbd-macro "<f5>") 'ispell-word)
;(global-set-key (read-kbd-macro "\C-cg") 'goto-line)


;; Man pages: Hitting F1 gives the man page for the library call 
;;            at the current cursor  position
(global-set-key [(f1)] (lambda () (interactive) (manual-entry (current-word))))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Some new Colors for Font-lock.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;(setq font-lock-mode-maximum-decoration t)
;(require 'font-lock)
;(setq font-lock-use-default-fonts nil)
;(setq font-lock-use-default-colors nil)
;(copy-face 'default 'font-lock-string-face)
;(set-face-foreground 'font-lock-string-face "Sienna")
;;(copy-face 'italic 'font-lock-comment-face)
;(set-face-foreground 'font-lock-comment-face "Red")
;(copy-face 'bold 'font-lock-function-name-face)
;(set-face-foreground 'font-lock-function-name-face "MediumBlue")
;(copy-face 'default 'font-lock-keyword-face)
;(set-face-foreground 'font-lock-keyword-face "SteelBlue")
;(copy-face 'default 'font-lock-type-face)
;(set-face-foreground 'font-lock-type-face "DarkOliveGreen")
;(GNUEmacs (set-face-foreground 'modeline "red")
;	  (set-face-background 'modeline "lemonchiffon"))

;(GNUEmacs
; (setq transient-mark-mode 't)
; )

;(GNUEmacs
; (Xlaunch
;  (make-face-bold 'bold-italic)
;  ))

;(set-face-foreground 'bold-italic "Blue")

;(setq default-frame-alist
;      '(
;;; Define here the default geometry or via ~/.Xdefaults.
;;	(width . 84) (height . 46)
;	(cursor-color . "red")
;	(cursor-type . box)
;	(foreground-color . "black")
;	(background-color . "honeydew")))

;;; A small exemples to show how Emacs is powerfull.
; Define function to match a parenthesis otherwise insert a %

;(global-set-key "%" 'match-paren)
;(defun match-paren (arg)
;  "Go to the matching parenthesis if on parenthesis otherwise insert %."
;  (interactive "p")
;  (cond ((looking-at "\\s\(") (forward-list 1) (backward-char 1))
;        ((looking-at "\\s\)") (forward-char 1) (backward-list 1))
;        (t (self-insert-command (or arg 1)))))

;;; By default turn on colorization.
;(if (fboundp 'global-font-lock-mode)
;    (global-font-lock-mode t)
;  )

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; C/C++ mode
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Coloring keywords in C C++ modes
;(global-font-lock-mode t)
;(setq font-lock-maximum-decoration
;           '((c-mode . 3) (c++-mode . 3)))

;;; gdb mode
(add-hook 'gdb-mode-hook
	  '(lambda () (local-set-key "\M-g" 'comint-bol)))
;;; Macro for C/C++
(add-hook 'c-mode-hook
          '(lambda ()
             (define-key c-mode-map "\C-c\C-c" 'compile)))

;;; Macro for C-space then C-i to indent region
;(global-set-key "\C-i" 'indent-region)

;;; manual: F1을 누르면 현재의 커서 위치에서 라이브러리 호출을 위한 맨 페이지를 보여 줌.
(global-set-key [(f1)] (lambda () (interactive) (manual-entry (current-word))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Running Perl script 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(add-hook 'perl-mode-hook
          '(lambda ()
              '(if (zerop (buffer-size))
                   (progn ))
              (executable-set-magic "perl" "-w")
              (set-buffer-modified-p nil) ; don't need?
              ))

;executable-set-magic: an interactive compiled Lisp function in `executable'.
;(executable-set-magic INTERPRETER &optional ARGUMENT NO-QUERY-FLAG INSERT-FLAG)

;;; RMIME provides MIME support for mh-e on Emacs. 
;;; For up to date information on the latest version of RMIME, please
;;; see http://www.cinti.net/~rmoody/rmime.
	(add-hook 'rmail-show-message-hook 'rmime-format)
	(add-hook 'rmail-edit-mode-hook    'rmime-cancel)
	(autoload 'rmime-format "rmime" "" nil)
;;; To use this file with mh-e, add the following to your .emacs file:
	(add-hook 'mh-show-mode-hook 'rmime-format)
	(autoload 'rmime-format "rmime" "" nil)
;; To use this file with VM, add the following to your .emacs file:
;	(setq vm-preview-lines t)
;	(add-hook 'vm-select-message-hook 'rmime-format)
;	(autoload 'rmime-format "rmime" "" nil)
;; To use this file manually, add the following to your .emacs file:
;;	(autoload 'rmime-mode   "rmime" "" t)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;             Mule: MultiLingual Emacs 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;(if (> emacs-major-version 19)
;    (progn
;      (set-language-environment 'Korean)
;      (standard-display-european t 'korean-ksc5601)
;      (set-input-mode nil nil 1))
;  (standard-display-european t))

;;; W3 mode
;;; to change w3 mode => "M-x w3" 
;(setq load-path (cons "/usr/local/src/w3-4/lisp/w3" load-path))

;;===================================================================
;; More information with the info file (Control-h i)
;; hangul setting
;; ,AGQ1[ ,A<3A$0z ,A0|7C5H ,A0M@: ,AGQ1[ Emacs ,A8^@O85 ,A8.=:F.?!<- 
;; ,AA$@g8q<jmjeong@oopsla.snu.ac.kr>,A4T22<- ,AC_C5GO=E ,A3;?k@T4O4Y.
;; ,AGQ1[ Eamcs ,A8^@O85 ,A8.=:F. emacs-kr@debian-kr.org,A@T4O4Y.
;;===================================================================
(require 'cl)
(when enable-multibyte-characters
  (set-language-environment "Korean")
  (setq-default file-name-coding-system 'euc-kr)
  ;;; ,A<<9z=D>2=C4B ,A:P5i@: ,A?)1b8& "3",A@87N ,A9Y2cAV<<?d.
  (setq default-korean-keyboard "")
  (setq input-method-verbose-flag nil
    input-method-highlight-flag nil)
  (prefer-coding-system 'euc-kr)
  (set-default-coding-systems 'euc-kr)
  ;; ,AD\<V ,A8p5e?!<- ,AGQ1[ ,ACb7B@; ,A@'GQ ,A<3A$@T4O4Y.
  (if (and (null window-system) (null noninteractive))
   (progn
    (set-keyboard-coding-system 'euc-kr)
     (set-terminal-coding-system 'euc-kr)))

  ;;(setq default-process-coding-system '(euc-kr . euc-kr))
  (when window-system (global-set-key "\C-\\" 'undefined))
  (add-hook 'quail-inactivate-hook 'delete-quail-completions)
  (defun delete-quail-completions ()
    (when (get-buffer "*Quail Completions*")
      (kill-buffer "*Quail Completions*")))
  (set-selection-coding-system 'iso-2022-kr)
  (setq-default sendmail-coding-system 'euc-kr)
  ;; turn off C-h during input
  (eval-after-load "quail"
    '(progn
      (define-key quail-translation-keymap "\C-h"
    'quail-delete-last-char)
      (define-key quail-translation-keymap "\C-?"
    'quail-translation-help)))
  (define-key global-map (read-kbd-macro "C-x RET s") 'decode-coding-region))

(global-set-key '[end]  'end-of-line)
(global-set-key '[home] 'beginning-of-line)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;                TeX mode commands.
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
(provide 'tex-mode)

(defvar TeX-saved-default-directory ""
  "*Directory added to the TEXINPUTS environment variable so that TeX or LaTeX can find include or input files.")
(defvar TeX-directory "~/tmp"
  "*Directory in which to run TeX subjob.  Temporary files are
created in this directory.")
(defvar TeX-dvi-print-command "dvips"
  "*Command string used by \\[TeX-print] to print a .dvi file.")
(defvar TeX-dvi-preview-command "xdvi"
  "*Command string used by \\[TeX-preview] to preview a .dvi file.")
(defvar TeX-show-queue-command "lpq"
  "*Command string used by \\[TeX-show-print-queue] to show the print queue
that \\[TeX-print] put your job on.")
(defvar TeX-default-mode 'plain-TeX-mode
  "*Mode to enter for a new file when it can't be determined whether
the file is plain TeX or LaTeX or what.")

(defvar TeX-command nil
  "The command to run TeX on a file.  The name of the file will be appended
to this string, separated by a space.")
(defvar TeX-trailer nil
  "String appended after the end of a region sent to TeX by \\[TeX-region].")
(defvar TeX-start-of-header nil
  "String used by \\[TeX-region] to delimit the start of the file's header.")
(defvar TeX-end-of-header nil
  "String used by \\[TeX-region] to delimit the end of the file's header.")
(defvar TeX-shell-cd-command "cd"
  "Command to give to shell running TeX to change directory.  The value of
TeX-directory will be appended to this, separated by a space.")
(defvar TeX-zap-file nil
  "Temporary file name used for text being sent as input to TeX.
Should be a simple file name with no extension or directory specification.")

(defvar TeX-mode-syntax-table nil
  "Syntax table used while in TeX mode.")

(defun TeX-define-common-keys (keymap)
  "Define the keys that we want defined both in TeX-mode
and in the TeX-shell."
  (define-key keymap "\C-c\C-k" 'TeX-kill-job)
  (define-key keymap "\C-c\C-l" 'TeX-recenter-output-buffer)
  (define-key keymap "\C-c\C-q" 'TeX-show-print-queue)
  (define-key keymap "\C-c\C-p" 'TeX-print)
  (define-key keymap "\C-c\C-v" 'TeX-preview)
  )

(defvar TeX-mode-map nil "Keymap for TeX mode")

(if TeX-mode-map 
    nil
  (setq TeX-mode-map (make-sparse-keymap))
  (TeX-define-common-keys TeX-mode-map)
  (define-key TeX-mode-map "\"" 'TeX-insert-quote)
  (define-key TeX-mode-map "\n" 'TeX-terminate-paragraph)
  (define-key TeX-mode-map "\e}" 'up-list)
  (define-key TeX-mode-map "\e{" 'TeX-insert-braces)
  (define-key TeX-mode-map "\C-c\C-r" 'TeX-region)
  (define-key TeX-mode-map "\C-c\C-b" 'TeX-buffer)
  (define-key TeX-mode-map "\C-c\C-f" 'TeX-close-LaTeX-block)
  )

(defvar TeX-shell-map nil
  "Keymap for the TeX shell.  A shell-mode-map with a few additions")

;(fset 'TeX-mode 'tex-mode) 		;in loaddefs.

;;; This would be a lot simpler if we just used a regexp search,
;;; but then it would be too slow.
(defun tex-mode ()
  "Major mode for editing files of input for TeX or LaTeX.
Trys to intuit whether this file is for plain TeX or LaTeX and
calls plain-tex-mode or latex-mode.  If it cannot be determined
\(e.g., there are no commands in the file), the value of
TeX-default-mode is used."
  (interactive)
  (let (mode slash comment)
    (save-excursion
      (goto-char (point-min))
      (while (and (setq slash (search-forward "\\" nil t))
		  (setq comment (let ((search-end (point)))
				  (save-excursion
				    (beginning-of-line)
				    (search-forward "%" search-end t))))))
      (if (and slash (not comment))
	  (setq mode (if (looking-at "documentstyle")
			 'latex-mode
		       'plain-tex-mode))))
    (if mode (funcall mode)
      (funcall TeX-default-mode))))

(fset 'plain-TeX-mode 'plain-tex-mode)
(fset 'LaTeX-mode 'latex-mode)

(defun plain-tex-mode ()
  "Major mode for editing files of input for plain TeX.
Makes $ and } display the characters they match.
Makes \" insert `` when it seems to be the beginning of a quotation,
and '' when it appears to be the end; it inserts \" only after a \\.

Use \\[TeX-region] to run TeX on the current region, plus a \"header\"
copied from the top of the file (containing macro definitions, etc.),
running TeX under a special subshell.  \\[TeX-buffer] does the whole buffer.  
\\[TeX-preview] previews the .dvi file made by either of these.
\\[TeX-print] prints the .dvi file made by either of these.

Use \\[validate-TeX-buffer] to check buffer for paragraphs containing
mismatched $'s or braces.

Special commands:
\\{TeX-mode-map}

Mode variables:
TeX-directory
	Directory in which to create temporary files for TeX jobs
	run by \\[TeX-region] or \\[TeX-buffer].
TeX-dvi-preview-command
	Command string used by \\[TeX-preview] to preview a .dvi file.
TeX-dvi-print-command
	Command string used by \\[TeX-print] to print a .dvi file.
TeX-show-queue-command
	Command string used by \\[TeX-show-print-queue] to show the print
	queue that \\[TeX-print] put your job on.

Entering plain-TeX mode calls the value of text-mode-hook,
then the value of TeX-mode-hook, and then the value
of plain-TeX-mode-hook."
  (interactive)
  (TeX-common-initialization)
  (setq mode-name "TeX")
  (setq major-mode 'plain-TeX-mode)
  (setq TeX-command "tex")
  (setq TeX-start-of-header "%**start of header")
  (setq TeX-end-of-header "%**end of header")
  (setq TeX-trailer "\\bye\n")
  (run-hooks 'text-mode-hook 'TeX-mode-hook 'plain-TeX-mode-hook))

(defun latex-mode ()
  "Major mode for editing files of input for LaTeX.
Makes $ and } display the characters they match.
Makes \" insert `` when it seems to be the beginning of a quotation,
and '' when it appears to be the end; it inserts \" only after a \\.

Use \\[TeX-region] to run LaTeX on the current region, plus the preamble
copied from the top of the file (containing \\documentstyle, etc.), running
LaTeX under a special subshell.  \\[TeX-buffer] does the whole buffer.
\\[TeX-preview] previews the .dvi file made by either of these.
\\[TeX-print] prints the .dvi file made by either of these.

Use \\[validate-TeX-buffer] to check buffer for paragraphs containing
mismatched $'s or braces.

Special commands:
\\{TeX-mode-map}

Mode variables:
TeX-directory
	Directory in which to create temporary files for TeX jobs
	run by \\[TeX-region] or \\[TeX-buffer].
TeX-dvi-preview-command
	Command string used by \\[TeX-preview] to preview a .dvi file.
TeX-dvi-print-command
	Command string used by \\[TeX-print] to print a .dvi file.
TeX-show-queue-command
	Command string used by \\[TeX-show-print-queue] to show the print
	queue that \\[TeX-print] put your job on.

Entering LaTeX mode calls the value of text-mode-hook,
then the value of TeX-mode-hook, and then the value
of LaTeX-mode-hook."
  (interactive)
  (TeX-common-initialization)
  (setq mode-name "LaTeX")
  (setq major-mode 'LaTeX-mode)
  (setq TeX-command "latex")
  (setq TeX-start-of-header "\\documentstyle")
  (setq TeX-end-of-header "\\begin{document}")
  (setq TeX-trailer "\\end{document}\n")
  (run-hooks 'text-mode-hook 'TeX-mode-hook 'LaTeX-mode-hook))

(defun TeX-common-initialization ()
  (kill-all-local-variables)
  (use-local-map TeX-mode-map)
  (setq local-abbrev-table text-mode-abbrev-table)
  (if (null TeX-mode-syntax-table)
      (progn
	(setq TeX-mode-syntax-table (make-syntax-table))
	(set-syntax-table TeX-mode-syntax-table)
	(modify-syntax-entry ?\\ ".")
	(modify-syntax-entry ?\f ">")
	(modify-syntax-entry ?\n ">")
	(modify-syntax-entry ?$ "$$")
	(modify-syntax-entry ?% "<")
	(modify-syntax-entry ?\" ".")
	(modify-syntax-entry ?& ".")
	(modify-syntax-entry ?_ ".")
	(modify-syntax-entry ?@ "_")
	(modify-syntax-entry ?~ " ")
	(modify-syntax-entry ?' "w"))
    (set-syntax-table TeX-mode-syntax-table))
  (make-local-variable 'paragraph-start)
  (setq paragraph-start "^[ \t]*$\\|^[\f\\\\%]")
  (make-local-variable 'paragraph-separate)
  (setq paragraph-separate paragraph-start)
  (make-local-variable 'comment-start)
  (setq comment-start "%")
  (make-local-variable 'comment-start-skip)
  (setq comment-start-skip "\\(\\(^\\|[^\\]\\)\\(\\\\\\\\\\)*\\)\\(%+ *\\)")
  (make-local-variable 'comment-indent-function)
  (setq comment-indent-function 'TeX-comment-indent)
  (make-local-variable 'TeX-command)
  (make-local-variable 'TeX-start-of-header)
  (make-local-variable 'TeX-end-of-header)
  (make-local-variable 'TeX-trailer))

(defun TeX-comment-indent ()
  (if (looking-at "%%%")
      (current-column)
    (skip-chars-backward " \t")
    (max (if (bolp) 0 (1+ (current-column)))
	 comment-column)))

(defun TeX-insert-quote (arg)
  "Insert ``, '' or \" according to preceding character.
With prefix argument, always insert \" characters."
  (interactive "P")
  (if arg
      (let ((count (prefix-numeric-value arg)))
	(if (listp arg)
	    (self-insert-command 1)	;C-u always inserts just one
	  (self-insert-command count)))
    (insert
     (cond
      ((or (bobp)
	   (save-excursion
	     (forward-char -1)
	     (looking-at "[ \t\n]\\|\\s(")))
       "``")
      ((= (preceding-char) ?\\)
       ?\")
      (t "''")))))

(defun validate-TeX-buffer ()
  "Check current buffer for paragraphs containing mismatched $'s.
As each such paragraph is found, a mark is pushed at its beginning,
and the location is displayed for a few seconds."
  (interactive)
  (let ((opoint (point)))
    (goto-char (point-max))
    ;; Does not use save-excursion
    ;; because we do not want to save the mark.
    (unwind-protect
	(while (and (not (input-pending-p)) (not (bobp)))
	  (let ((end (point)))
	    (search-backward "\n\n" nil 'move)
	    (or (TeX-validate-paragraph (point) end)
		(progn
		  (push-mark (point))
		  (message "Mismatch found in pararaph starting here")
		  (sit-for 4)))))
      (goto-char opoint))))

(defun TeX-validate-paragraph (start end)
  (condition-case ()
      (save-excursion
	(save-restriction
	  (narrow-to-region start end)
	  (goto-char start)
	  (forward-sexp (- end start))
	  t))
    (error nil)))

(defun TeX-terminate-paragraph (inhibit-validation)
  "Insert two newlines, breaking a paragraph for TeX.
Check for mismatched braces/$'s in paragraph being terminated.
A prefix arg inhibits the checking."
  (interactive "P")
  (or inhibit-validation
      (TeX-validate-paragraph
       (save-excursion
	 (search-backward "\n\n" nil 'move)
	 (point))
       (point))
      (message "Paragraph being closed appears to contain a mismatch"))
  (insert "\n\n"))

(defun TeX-insert-braces ()
  "Make a pair of braces and be poised to type inside of them."
  (interactive)
  (insert ?\{)
  (save-excursion
    (insert ?})))

;;; Like TeX-insert-braces, but for LaTeX.
(defun TeX-close-LaTeX-block ()
  "Creates an \\end{...} to match \\begin{...} on the current line and
puts point on the blank line between them."
  (interactive "*")
  (let ((fail-point (point)))
    (end-of-line)
    (if (re-search-backward "\\\\begin{\\([^}\n]*\\)}"
			    (save-excursion (beginning-of-line) (point)) t)
	(let ((text (buffer-substring (match-beginning 1) (match-end 1)))
	      (indentation (current-column)))
	  (end-of-line)
	  (delete-horizontal-space)
	  (insert "\n\n")
	  (indent-to indentation)
	  (insert "\\end{" text "}")
	  (forward-line -1))
      (goto-char fail-point)
      (ding))))

;;; Invoking TeX in an inferior shell.

;;; Why use a shell instead of running TeX directly?  Because if TeX
;;; gets stuck, the user can switch to the shell window and type at it.

;;; The utility functions:

(defun TeX-start-shell ()
  (require 'shell)
  (save-excursion
    (set-buffer (make-shell "TeX-shell" nil nil "-v"))
    (setq TeX-shell-map (copy-keymap shell-mode-map))
    (TeX-define-common-keys TeX-shell-map)
    (use-local-map TeX-shell-map)
    (if (zerop (buffer-size))
	(sleep-for 1))))

(defun set-buffer-directory (buffer directory)
  "Set BUFFER's default directory to be DIRECTORY."
  (setq directory (file-name-as-directory (expand-file-name directory)))
  (if (not (file-directory-p directory))
      (error "%s is not a directory" directory)
    (save-excursion
      (set-buffer buffer)
      (setq default-directory directory))))

;;; The commands:

;;; It's a kludge that we have to create a special buffer just 
;;; to write out the TeX-trailer.  It would nice if there were a
;;; function like write-region that would write literal strings.

(defun TeX-region (beg end)
  "Run TeX on the current region.  A temporary file (TeX-zap-file) is
written in directory TeX-directory, and TeX is run in that directory.
If the buffer has a header, it is written to the temporary file before
the region itself.  The buffer's header is all lines between the
strings defined by TeX-start-of-header and TeX-end-of-header
inclusive.  The header must start in the first 100 lines.  The value
of TeX-trailer is appended to the temporary file after the region."
  (interactive "r")
  (if (get-buffer "*TeX-shell*")
      (TeX-kill-job)
    (TeX-start-shell))
  (or TeX-zap-file
      (let ((basename (file-name-nondirectory buffer-file-name)))
	(setq TeX-zap-file (substring basename 0 
				      (string-match "\\.tex$" basename)))))
  (message "%s" TeX-zap-file)
  (let ((tex-out-file (concat TeX-zap-file ".tex"))
	(temp-buffer (get-buffer-create " TeX-Output-Buffer"))
	(zap-directory
	 (file-name-as-directory (expand-file-name TeX-directory))))
    (save-excursion
      (save-restriction
	(widen)
	(goto-char (point-min))
	(forward-line 100)
	(let ((search-end (point))
	      (hbeg (point-min)) (hend (point-min))
	      (default-directory zap-directory))
	  (goto-char (point-min))

;;; Initialize the temp file with either the header or nothing
	  (if (search-forward TeX-start-of-header search-end t)
	      (progn
		(beginning-of-line)
		(setq hbeg (point))	;mark beginning of header
		(if (search-forward TeX-end-of-header nil t)
		    (progn (forward-line 1)
			   (setq hend (point)))	;mark end of header
		  (setq hbeg (point-min))))) ;no header
	  (write-region (min hbeg beg) hend tex-out-file nil nil)
	  (write-region (max beg hend) end tex-out-file t nil))
	(let ((local-tex-trailer TeX-trailer))
	  (set-buffer temp-buffer)
	  (erase-buffer)

;;; make sure trailer isn't hidden by a comment
	  (insert-string "\n")
	  (if local-tex-trailer (insert-string local-tex-trailer))
	  (set-buffer-directory temp-buffer zap-directory)
	  (write-region (point-min) (point-max) tex-out-file t nil))))
    (set-buffer-directory "*TeX-shell*" zap-directory)
    (if (not (eq TeX-saved-default-directory default-directory))
	(progn
	  (message "%s" "setting dir")
	  (send-string "TeX-shell" (concat "setenv TEXINPUTS \""
					   default-directory
					   ":$TEXINPUTS\" \n"))
	  (setq TeX-saved-default-directory default-directory)))
    (send-string "TeX-shell" (concat TeX-shell-cd-command " "
				     zap-directory "\n"))
    (send-string "TeX-shell" (concat TeX-command " \""
				     tex-out-file "\"\n")))
  (TeX-recenter-output-buffer 0))

(defun TeX-buffer ()
  "Run TeX on current buffer.  See \\[TeX-region] for more information."
  (interactive)
  (TeX-region (point-min) (point-max)))

(defun TeX-kill-job ()
  "Kill the currently running TeX job."
  (interactive)
  (quit-process "TeX-shell" t))

(defun TeX-recenter-output-buffer (linenum)
  "Redisplay buffer of TeX job output so that most recent output can be seen.
The last line of the buffer is displayed on
line LINE of the window, or centered if LINE is nil."
  (interactive "P")
  (let ((tex-shell (get-buffer "*TeX-shell*"))
	(old-buffer (current-buffer)))
    (if (null tex-shell)
	(message "No TeX output buffer")
      (pop-to-buffer tex-shell)
      (bury-buffer tex-shell)
      (goto-char (point-max))
      (recenter (if linenum
		    (prefix-numeric-value linenum)
		  (/ (window-height) 2)))
      (pop-to-buffer old-buffer)
      )))

(defun TeX-preview ()
  "Preview the .dvi file made by \\[TeX-region] or \\[TeX-buffer].
Runs the shell command defined by TeX-dvi-preview-command."
  (interactive)
  (send-string "TeX-shell"
	       (concat TeX-dvi-preview-command " \"" TeX-zap-file ".dvi\"\n"))
  (TeX-recenter-output-buffer nil))

(defun TeX-print ()
  "Print the .dvi file made by \\[TeX-region] or \\[TeX-buffer].
Runs the shell command defined by TeX-dvi-print-command."
  (interactive)
  (send-string "TeX-shell"
	       (concat TeX-dvi-print-command " \"" TeX-zap-file ".dvi\"\n"))
  (TeX-recenter-output-buffer nil))

(defun TeX-show-print-queue ()
  "Show the print queue that \\[TeX-print] put your job on.
Runs the shell command defined by TeX-show-queue-command."
  (interactive)
  (if (not (get-buffer "*TeX-shell*"))
      (TeX-start-shell))
  (send-string "TeX-shell" (concat TeX-show-queue-command "\n"))
  (TeX-recenter-output-buffer nil))

(put 'eval-expression 'disabled nil)

;;;
;;;
(fset 'turn-on-fill
   "xindented-text-mode
")
(global-set-key "6" 'turn-on-fill)

(fset 'turn-off-fill
   "xtext mode
.")
(global-set-key "7" 'turn-off-fill)

(fset 'indent-it
   "xindent-relative
")
(local-set-key "8" 'indent-it)


(setq billomove nil)

(defun move-set-up ()
  "set up for a cursor move"
  (interactive)
  (setq billomove t))

(global-set-key "[" 'move-set-up)


(defun chooseA ()
  "either move cursor or insert A"
  (interactive)
  (if billomove (progn (setq billomove nil)(previous-line 1)) (insert-char 65 1))
)

(global-set-key "A" 'chooseA)

(defun chooseB ()
  "either move cursor or insert B"
  (interactive)
  (if billomove (progn (setq billomove nil)(next-line 1)) (insert-char 66 1))
)

(global-set-key "B" 'chooseB)

(defun chooseC ()
  "either move cursor or insert C"
  (interactive)
  (if billomove (progn (setq billomove nil)(forward-char 1)) (insert-char 67 1))
)

(global-set-key "C" 'chooseC)

(defun chooseD ()
  "either move cursor or insert D"
  (interactive)
  (if billomove (progn (setq billomove nil)(backward-char 1)) (insert-char 68 1))
)

(global-set-key "D" 'chooseD)

(setq auto-mode-alist (mapcar 'purecopy
			      '(("\\.c$" . c++-mode)
				("\\.cs$" . c++-mode)
				("\\.h$" . c++-mode)
				("\\.c++$" . c++-mode)
				("\\.C$" . c++-mode)
				("\\.cc$" . c++-mode)
				("\\.cpp$" . c++-mode)
				("\\.CPP$" . c++-mode)
				("\\.fcm$" . fortran-mode)
				("\\.text$" . text-mode)
				("\\.tex$" . TeX-mode)
				("\\.el$" . emacs-lisp-mode)
				("\\.scm$" . scheme-mode)
				("\\.l$" . lisp-mode)
				("\\.lisp$" . lisp-mode)
				("\\.f$" . fortran-mode)
				("\\.mss$" . scribe-mode)
				("\\.pl$" . prolog-mode)
;;; Less common extensions come here
;;; so more common ones above are found faster.
				("\\.TeX$" . TeX-mode)
				("\\.sty$" . LaTeX-mode)
				("\\.bbl$" . LaTeX-mode)
				("\\.bib$" . text-mode)
				("\\.article$" . text-mode)
				("\\.letter$" . text-mode)
				("\\.texinfo$" . texinfo-mode)
				("\\.lsp$" . lisp-mode)
				("\\.prolog$" . prolog-mode)
				;; Mailer puts message to be edited in /tmp/Re.... or Message
				("^/tmp/Re" . text-mode)
				;; some news reader is reported to use this
				("^/tmp/fol/" . text-mode)
				("/Message[0-9]*$" . text-mode)
				("\\.y$" . c-mode)
				("\\.scm.[0-9]*$" . scheme-mode)
				;; .emacs following a directory delimiter
				;; in either Unix or VMS syntax.
				("[]>:/]\\..*emacs" . emacs-lisp-mode)
				("\\.ml$" . lisp-mode))))

(setq minibuffer-max-depth nil)


;;; Display line number and column number on the bar of minibuffer
;(line-number-mode 't)
;;; or
;(setq load-path (cons "/amd/serval/serval3/users/bkna/.emacsrs" load-path))
;(setq load-path (append (list (expand-file-name "column.el")) load-path))
;(autoload 'display-column-mode "column" nil t) ;type M-x display-column mode 
;(display-column-mode 1) ;auto display coulumn number.
;;; or
;;; For Line number and Column number
(setq-default line-number-mode t)
(setq-default column-number-mode t)

;; Options Menu Settings
;; =====================
(cond
 ((and (string-match "XEmacs" emacs-version)
       (boundp 'emacs-major-version)
       (or (and
            (= emacs-major-version 19)
            (>= emacs-minor-version 14))
           (= emacs-major-version 20))
       (fboundp 'load-options-file))
  (load-options-file ".xemacs-options")))
;; ============================
;; End of Options Menu Settings


;;===================================================================
;; GNUS
;;===================================================================

;; make Gnus start faster
(setq gnus-check-new-newsgroups nil
      gnus-read-active-file 'some
      gnus-nov-is-evil nil)

(setq gnus-select-method '(nntp "nntp.localdomain"))

(setq message-default-news-headers "MIME-Version: 1.0\nContent-Type: text/plain; charset=EUC-KR\nContent-Transfer-Encoding: 8bit\n")


;;; ==================================================================
;;; Scrolling on mouse wheel 
;;; ==================================================================




      (defun up-slightly () (interactive) (scroll-up 5))
      (defun down-slightly () (interactive) (scroll-down 5))
      (global-set-key [mouse-4] 'down-slightly)
      (global-set-key [mouse-5] 'up-slightly)
      
      (defun up-one () (interactive) (scroll-up 1))
      (defun down-one () (interactive) (scroll-down 1))
      (global-set-key [S-mouse-4] 'down-one)
      (global-set-key [S-mouse-5] 'up-one)
      
      
      (defun up-a-lot () (interactive) (scroll-up))
      (defun down-a-lot () (interactive) (scroll-down))
      (global-set-key [C-mouse-4] 'down-a-lot)
      (global-set-key [C-mouse-5] 'up-a-lot)
      

      
;;;;;;;;;;;;;;;;; End of .emacs ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;