#include "MarkdownHighlighter.h"
#include <QColor>

MarkdownHighlighter::MarkdownHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    // Header formats (# ## ###)
    headerFormat.setForeground(QColor(86, 156, 214)); // Blue
    headerFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("^#{1,6}\\s.*"));
    rule.format = headerFormat;
    highlightingRules.append(rule);

    // Bold text (**text**)
    boldFormat.setForeground(QColor(220, 220, 170)); // Light yellow
    boldFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("\\*\\*([^*]+)\\*\\*"));
    rule.format = boldFormat;
    highlightingRules.append(rule);

    // Italic text (*text*)
    italicFormat.setForeground(QColor(220, 220, 170)); // Light yellow
    italicFormat.setFontItalic(true);
    rule.pattern = QRegularExpression(QStringLiteral("\\*([^*]+)\\*"));
    rule.format = italicFormat;
    highlightingRules.append(rule);

    // Inline code (`code`)
    codeFormat.setForeground(QColor(206, 145, 120)); // Orange
    codeFormat.setBackground(QColor(40, 44, 52)); // Dark background
    codeFormat.setFontFamilies(QStringList() << "Monaco" << "Consolas" << "monospace");
    rule.pattern = QRegularExpression(QStringLiteral("`([^`]+)`"));
    rule.format = codeFormat;
    highlightingRules.append(rule);

    // Code blocks (```)
    rule.pattern = QRegularExpression(QStringLiteral("```[^`]*```"));
    rule.format = codeFormat;
    highlightingRules.append(rule);

    // Links [text](url)
    linkFormat.setForeground(QColor(79, 193, 255)); // Light blue
    linkFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
    rule.pattern = QRegularExpression(QStringLiteral("\\[([^\\]]+)\\]\\(([^)]+)\\)"));
    rule.format = linkFormat;
    highlightingRules.append(rule);

    // Lists (- * +)
    listFormat.setForeground(QColor(156, 220, 254)); // Light blue
    listFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("^\\s*[\\-\\*\\+]\\s"));
    rule.format = listFormat;
    highlightingRules.append(rule);

    // Numbered lists (1. 2. etc.)
    rule.pattern = QRegularExpression(QStringLiteral("^\\s*\\d+\\.\\s"));
    rule.format = listFormat;
    highlightingRules.append(rule);

    // Blockquotes (>)
    blockquoteFormat.setForeground(QColor(106, 153, 85)); // Green
    blockquoteFormat.setFontItalic(true);
    rule.pattern = QRegularExpression(QStringLiteral("^>.*"));
    rule.format = blockquoteFormat;
    highlightingRules.append(rule);
}

void MarkdownHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}